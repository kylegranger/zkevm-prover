#include "database_associative_cache.hpp"
#include "scalar.hpp"
#include "zklog.hpp"
#include "zkmax.hpp"
#include "timer.hpp"
#include "zkassert.hpp"

// DatabaseAssociativeCache class implementation
// Add a record in the head of the cache. Returns true if the cache is full (or no cache), false otherwise
bool DatabaseAssociativeCache::addKeyValue(const uint64_t index, const string &remainingKey, const void *value, const bool update, const string &leftChildkey, const string &rightChildKey)
{

    if (nKeyBits == 0)
    {
        return true;
    }

    attempts++;
    if (attempts << 44 == 0)
    {
        zklog.info("DatabaseAssociativeCache::addKeyValue() name=" + name + " cacheSize=" + to_string(size) + " attempts=" + to_string(attempts) + " hits=" + to_string(hits) + " hit ratio=" + to_string(double(hits) * 100.0 / double(zkmax(attempts, 1))) + "%");
    }

    DatabaseAssociativeCacheRecord *record;
    // If key already exists in the cache return. The findKey also sets the record in the head of the cache
    if (findKey(index, remainingKey, record))
    {
        if (update)
        {
            updateRecord(record, value, leftChildkey, rightChildKey);
            return false;
        }
        else
        {
            hits++;
            return false;
        }
    }

    record = allocRecord(remainingKey, value, leftChildkey, rightChildKey);
    buffer[index] = record;
    /*vector<Goldilocks::Element> &auxvalue = *((vector<Goldilocks::Element>*) record->value);
    Goldilocks fr;
    string auxLeftChildKey = fea2string(fr, auxvalue[0], auxvalue[1], auxvalue[2], auxvalue[3]);
    string auxRighChildKey = fea2string(fr, auxvalue[4], auxvalue[5], auxvalue[6], auxvalue[7]);
    auxLeftChildKey = NormalizeToNFormat(auxLeftChildKey, 64);
    auxLeftChildKey = stringToLower(auxLeftChildKey);
    auxRighChildKey = NormalizeToNFormat(auxRighChildKey, 64);
    auxRighChildKey = stringToLower(auxRighChildKey);
    if(auxLeftChildKey != leftChildkey || auxRighChildKey != rightChildKey){
        
        zklog.error("DatabaseAssociativeCache::addKeyValue() leftChildKey=" + leftChildkey + " rightChildKey=" + rightChildKey);
        zklog.error("DatabaseAssociativeCache::addKeyValue() auxLeftChildKey=" + auxLeftChildKey + " auxRighChildKey=" + auxRighChildKey);
        //exitProcess();
    }*/

    return false;
}
bool DatabaseAssociativeCache::findKey(const uint64_t index, const string &remainingKey, DatabaseAssociativeCacheRecord *&record)
{

    if (nKeyBits == 0 || buffer[index] == NULL || buffer[index]->remainingKey != remainingKey)
    {
        return false;
    }
    ++hits;
    record = buffer[index];
    return true;
}

bool DatabaseAssociativeCache::addKeyValue(Goldilocks::Element (&key)[4], const vector<Goldilocks::Element> &value,  const bool update)
{
    //rick: update has not much sense right?
    if (nKeyBits == 0)
    {
        return true;
    }

    attempts++;
    if (attempts << 44 == 0)
    {
        zklog.info("DatabaseAssociativeCache::addKeyValue() name=" + name + " cacheSize=" + to_string(size) + " attempts=" + to_string(attempts) + " hits=" + to_string(hits) + " hit ratio=" + to_string(double(hits) * 100.0 / double(zkmax(attempts, 1))) + "%");
    }

    uint32_t index = (uint32_t)(key[0].fe & indexMask);
    uint32_t offset = indices_[index]*16;
    bool isleaf = value.size() > 8;
    if(buffer_[offset] == key[0].fe && buffer_[offset+1] == key[1].fe && buffer_[offset+2] == key[2].fe && buffer_[offset+3] == key[3].fe){
        hits++; //rick: this part can be omited
    }else{
        buffer_pos +=1;
        indices_[index] = buffer_pos;
        offset = indices_[index]*16;
        buffer_[offset] = key[0].fe;
        buffer_[offset+1] = key[1].fe;
        buffer_[offset+2] = key[2].fe;
        buffer_[offset+3] = key[3].fe;
        buffer_[offset+4] = value[0].fe;
        buffer_[offset+5] = value[1].fe;
        buffer_[offset+6] = value[2].fe;
        buffer_[offset+7] = value[3].fe;
        buffer_[offset+8] = value[4].fe;
        buffer_[offset+9] = value[5].fe;
        buffer_[offset+10] = value[6].fe;
        buffer_[offset+11] = value[7].fe;
        if(isleaf){
            buffer_[offset+12] = value[8].fe;
            buffer_[offset+13] = value[9].fe;
            buffer_[offset+14] = value[10].fe;
            buffer_[offset+15] = value[11].fe;
        }else{
            buffer_[offset+12] = 0xFFFFFFFFFFFFFFFF;
        }
    }
    return false;
}
bool DatabaseAssociativeCache::findKey(Goldilocks::Element (&key)[4], vector<Goldilocks::Element> &value)
{
    uint32_t index = (uint32_t)(key[0].fe & indexMask);
    uint32_t offset = indices_[index]*16;
    if(buffer_[offset] == key[0].fe && buffer_[offset+1] == key[1].fe && buffer_[offset+2] == key[2].fe && buffer_[offset+3] == key[3].fe){
        ++hits;
        bool isleaf = (buffer_[offset+12] != 0xFFFFFFFFFFFFFFFF);
        if(isleaf){
            value.resize(12);
        }else{
            value.resize(8);
        }
        value[0].fe = buffer_[offset+4];
        value[1].fe = buffer_[offset+5];
        value[2].fe = buffer_[offset+6];
        value[3].fe = buffer_[offset+7];
        value[4].fe = buffer_[offset+8];
        value[5].fe = buffer_[offset+9];
        value[6].fe = buffer_[offset+10];
        value[7].fe = buffer_[offset+11];
        if(isleaf){
            value[8].fe = buffer_[offset+12];
            value[9].fe = buffer_[offset+13];
            value[10].fe = buffer_[offset+14];
            value[11].fe = buffer_[offset+15];
        }
        return true;
    }
    return false;
}

// DatabaseMTAssociativeCach class implementation
DatabaseAssociativeCacheRecord *DatabaseMTAssociativeCache::allocRecord(const string remainingKey, const void *value, const string &leftChildkey, const string &rightChildKey)
{
    // Allocate memory
    DatabaseAssociativeCacheRecord *pRecord = new (DatabaseAssociativeCacheRecord);
    if (pRecord == NULL)
    {
        zklog.error("DatabaseMTAssociativeCache::allocRecord() failed calling new(DatabaseAssociativeCacheRecord)");
        exitProcess();
    }
    vector<Goldilocks::Element> *pValue = new (vector<Goldilocks::Element>);
    if (pValue == NULL)
    {
        zklog.error("DatabaseMTAssociativeCache::allocRecord() failed calling new(vector<Goldilocks::Element>)");
        exitProcess();
    }

    // Copy vector
    *pValue = *(const vector<Goldilocks::Element> *)value;

    // Assign values to record
    pRecord->value = pValue;
    pRecord->remainingKey = remainingKey;
    pRecord->leftChildKey = leftChildkey;
    pRecord->rightChildKey = rightChildKey;
        
    return pRecord;
}

// DatabaseProgramAssociativeCache class implementation
DatabaseAssociativeCacheRecord *DatabaseProgramAssociativeCache::allocRecord(const string remainingKey, const void *value, const string &leftChildkey, const string &rightChildKey)
{
    // Allocate memory
    DatabaseAssociativeCacheRecord *pRecord = new (DatabaseAssociativeCacheRecord);
    if (pRecord == NULL)
    {
        zklog.error("DatabaseProgramAssociativeCache::allocRecord() failed calling new(DatabaseAssociativeCacheRecord)");
        exitProcess();
    }
    vector<uint8_t> *pValue = new (vector<uint8_t>);
    if (pValue == NULL)
    {
        zklog.error("DatabaseProgramAssociativeCache::allocRecord() failed calling new(vector<uint8_t>)");
        exitProcess();
    }

    // Copy vector
    *pValue = *(const vector<uint8_t> *)value;

    // Assign values to record
    pRecord->value = pValue;
    pRecord->remainingKey = remainingKey;
    pRecord->leftChildKey = leftChildkey;
    pRecord->rightChildKey = rightChildKey;
        
    return pRecord;
}

// TODO:
// 1.Use ramaining key whenever possible
// 2.Avoid using pointers in the cache, use templates instead
// 3.Currently desctructor is not correct because it does not call the free function
// 4.conflict: understand conflics in write orderings
// 5.understand when we use 8 or 12 values