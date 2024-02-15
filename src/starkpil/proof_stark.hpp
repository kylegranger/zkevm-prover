#ifndef PROOF
#define PROOF

#include "goldilocks_base_field.hpp"
#include "poseidon_goldilocks.hpp"
#include "stark_info.hpp"
#include "fr.hpp"
#include <vector>
#include "nlohmann/json.hpp"

using ordered_json = nlohmann::ordered_json;

template <typename ElementType>
std::string toString(const ElementType& element);

template<>
inline std::string toString(const Goldilocks::Element& element) {
    return Goldilocks::toString(element);
}

template<>
inline std::string toString(const RawFr::Element& element) {
    return RawFr::field.toString(element, 10);
}

template <typename ElementType>
class MerkleProof
{
public:
    std::vector<std::vector<Goldilocks::Element>> v;
    std::vector<std::vector<ElementType>> mp;

    MerkleProof(uint64_t nLinears, uint64_t elementsTree, uint64_t elementsTreeSize, void *pointer) : v(nLinears, std::vector<Goldilocks::Element>(1, Goldilocks::zero())), mp(elementsTree, std::vector<ElementType>(elementsTreeSize))
    {
        for (uint64_t i = 0; i < nLinears; i++)
        {
            std::memcpy(&v[i][0], &((Goldilocks::Element *)pointer)[i], sizeof(Goldilocks::Element));
        }
        ElementType *mpCursor = (ElementType *)&((Goldilocks::Element *)pointer)[nLinears];
        for (uint64_t j = 0; j < elementsTree; j++)
        {
            std::memcpy(&mp[j][0], &mpCursor[j * elementsTreeSize], elementsTreeSize * sizeof(ElementType));
        }
    }

    ordered_json merkleProof2json()
    {
        ordered_json j = ordered_json::array();
        ordered_json json_v = ordered_json::array();
        for (uint i = 0; i < v.size(); i++)
        {
            if (v[i].size() > 1)
            {
                ordered_json element = ordered_json::array();
                for (uint j = 0; j < v[i].size(); j++)
                {
                    element.push_back(Goldilocks::toString(v[i][j]));
                }
                json_v.push_back(element);
            }
            else
            {
                json_v.push_back(Goldilocks::toString(v[i][0]));
            }
        }
        j.push_back(json_v);

        ordered_json json_mp = ordered_json::array();
        for (uint i = 0; i < mp.size(); i++)
        {
            ordered_json element = ordered_json::array();
            for (uint j = 0; j < mp[i].size(); j++)
            {
                element.push_back(toString(mp[i][j]));
            }
            json_mp.push_back(element);
        }
        j.push_back(json_mp);
        return j;
    }
};

template <typename ElementType>
class ProofTree
{
public:
    std::vector<ElementType> root;
    std::vector<std::vector<MerkleProof<ElementType>>> polQueries;

    uint64_t elementSize;

    ProofTree(uint64_t elementSize) : root(elementSize), elementSize(elementSize) {}

    void setRoot(ElementType *_root)
    {
        std::memcpy(&root[0], &_root[0], elementSize * sizeof(ElementType));
    };

    ordered_json ProofTree2json()
    {
        ordered_json j_ProofTree2json = ordered_json::object();

        ordered_json json_root = ordered_json::array();
        if(root.size() == 1) {
            j_ProofTree2json["root"] = toString(root[0]);
        } else {
            for (uint i = 0; i < root.size(); i++)
            {
                json_root.push_back(toString(root[i]));
            }
            j_ProofTree2json["root"] = json_root;
        }

        ordered_json json_polQueries = ordered_json::array();
        for (uint i = 0; i < polQueries.size(); i++)
        {
            ordered_json element = ordered_json::array();
            if (polQueries[i].size() != 1)
            {
                for (uint j = 0; j < polQueries[i].size(); j++)
                {
                    element.push_back(polQueries[i][j].merkleProof2json());
                }
                json_polQueries.push_back(element);
            }
            else
            {
                json_polQueries.push_back(polQueries[i][0].merkleProof2json());
            }
        }

        j_ProofTree2json["polQueries"] = json_polQueries;

        return j_ProofTree2json;
    }
};

template <typename ElementType>
class Fri
{
public:
    std::vector<std::vector<Goldilocks::Element>> pol;
    std::vector<ProofTree<ElementType>> trees;

    Fri(StarkInfo starkInfo, int64_t elementSize) : pol(1 << starkInfo.starkStruct.steps[starkInfo.starkStruct.steps.size() - 1].nBits, std::vector<Goldilocks::Element>(FIELD_EXTENSION, Goldilocks::zero())),
                                                             trees(starkInfo.starkStruct.steps.size(), elementSize) {}

    void setPol(Goldilocks::Element *pPol)
    {
        for (uint64_t i = 0; i < pol.size(); i++)
        {
            std::memcpy(&pol[i][0], &pPol[i * pol[i].size()], pol[i].size() * sizeof(Goldilocks::Element));
        }
    }

    ordered_json FriP2json()
    {
        ordered_json j = ordered_json::array();

        for (uint i = 0; i < trees.size(); i++)
        {
            j.push_back((trees[i].ProofTree2json()));
        }

        ordered_json json_pol = ordered_json::array();
        for (uint i = 0; i < pol.size(); i++)
        {
            ordered_json element = ordered_json::array();
            for (uint j = 0; j < pol[i].size(); j++)
            {
                element.push_back(Goldilocks::toString(pol[i][j]));
            }
            json_pol.push_back(element);
        }
        j.push_back(json_pol);
        return j;
    }
};

template <typename ElementType>
class Proofs
{
public:
    uint64_t elementSize;
    uint64_t nStages;
    ElementType **roots;
    Fri<ElementType> fri;
    std::vector<std::vector<Goldilocks::Element>> evals;
    Proofs(StarkInfo starkInfo, uint64_t elementSize) :
        elementSize(elementSize),
        fri(starkInfo, elementSize),
        evals(starkInfo.evMap.size(), std::vector<Goldilocks::Element>(FIELD_EXTENSION, Goldilocks::zero()))
        {
            nStages = starkInfo.nStages + 1;
            roots = new ElementType*[nStages];
            for(uint64_t i = 0; i < nStages; i++)
            {
                roots[i] = new ElementType[elementSize];
            }
        };

    ~Proofs() {
        for (uint64_t i = 0; i < nStages; ++i) {
            delete[] roots[i];
        }
        delete[] roots;
    }

    void setEvals(Goldilocks::Element *_evals)
    {
        for (uint64_t i = 0; i < evals.size(); i++)
        {
            std::memcpy(&evals[i][0], &_evals[i * evals[i].size()], evals[i].size() * sizeof(Goldilocks::Element));
        }
    }

    ordered_json proof2json()
    {
        ordered_json j = ordered_json::object();

        for(uint64_t i = 0; i < nStages; i++) {
            ordered_json json_root = ordered_json::array();
            if(elementSize == 1) {
                j["root" + to_string(i + 1)] = toString(roots[i][0]);
            } else {
                for (uint k = 0; k < elementSize; k++)
                {
                    json_root.push_back(toString(roots[i][k]));
                }
                j["root" + to_string(i + 1)] = json_root;
            }
        }

        ordered_json json_evals = ordered_json::array();
        for (uint i = 0; i < evals.size(); i++)
        {
            ordered_json element = ordered_json::array();
            for (uint j = 0; j < evals[i].size(); j++)
            {
                element.push_back(Goldilocks::toString(evals[i][j]));
            }
            json_evals.push_back(element);
        }
        j["evals"] = json_evals;
        j["fri"] = fri.FriP2json();
        return j;
    }
};

template <typename ElementType>
class FRIProof
{
public:
    Proofs<ElementType> proofs;
    std::vector<ElementType> publics;

    FRIProof(StarkInfo starkInfo, uint64_t elementSize) : proofs(starkInfo, elementSize), publics(starkInfo.nPublics){};
};

#endif