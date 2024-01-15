// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: multichain.proto
#ifndef GRPC_multichain_2eproto__INCLUDED
#define GRPC_multichain_2eproto__INCLUDED

#include "multichain.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace multichain {
namespace v1 {

// timestamps are represented in unix time in seconds
//
// *
// Define all methods implementes by the gRPC
// Channel: prover receives multichain messages and returns prover messages with the same id
class MultichainService final {
 public:
  static constexpr char const* service_full_name() {
    return "multichain.v1.MultichainService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>> Channel(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>>(ChannelRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>> AsyncChannel(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>>(AsyncChannelRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>> PrepareAsyncChannel(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>>(PrepareAsyncChannelRaw(context, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void Channel(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::multichain::v1::ProverMessage,::multichain::v1::MultichainMessage>* reactor) = 0;
      #else
      virtual void Channel(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::multichain::v1::ProverMessage,::multichain::v1::MultichainMessage>* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>* ChannelRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>* AsyncChannelRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>* PrepareAsyncChannelRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    std::unique_ptr< ::grpc::ClientReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>> Channel(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>>(ChannelRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>> AsyncChannel(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>>(AsyncChannelRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>> PrepareAsyncChannel(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>>(PrepareAsyncChannelRaw(context, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void Channel(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::multichain::v1::ProverMessage,::multichain::v1::MultichainMessage>* reactor) override;
      #else
      void Channel(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::multichain::v1::ProverMessage,::multichain::v1::MultichainMessage>* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>* ChannelRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>* AsyncChannelRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>* PrepareAsyncChannelRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Channel_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Channel(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::multichain::v1::MultichainMessage, ::multichain::v1::ProverMessage>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_Channel : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Channel() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Channel() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Channel(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::multichain::v1::MultichainMessage, ::multichain::v1::ProverMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestChannel(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::multichain::v1::MultichainMessage, ::multichain::v1::ProverMessage>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Channel<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_Channel : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_Channel() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc_impl::internal::CallbackBidiHandler< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context) { return this->Channel(context); }));
    }
    ~ExperimentalWithCallbackMethod_Channel() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Channel(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::multichain::v1::MultichainMessage, ::multichain::v1::ProverMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerBidiReactor< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>* Channel(
      ::grpc::CallbackServerContext* /*context*/)
    #else
    virtual ::grpc::experimental::ServerBidiReactor< ::multichain::v1::ProverMessage, ::multichain::v1::MultichainMessage>* Channel(
      ::grpc::experimental::CallbackServerContext* /*context*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_Channel<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_Channel<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Channel : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Channel() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Channel() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Channel(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::multichain::v1::MultichainMessage, ::multichain::v1::ProverMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Channel : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Channel() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Channel() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Channel(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::multichain::v1::MultichainMessage, ::multichain::v1::ProverMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestChannel(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_Channel : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_Channel() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc_impl::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context) { return this->Channel(context); }));
    }
    ~ExperimentalWithRawCallbackMethod_Channel() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Channel(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::multichain::v1::MultichainMessage, ::multichain::v1::ProverMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* Channel(
      ::grpc::CallbackServerContext* /*context*/)
    #else
    virtual ::grpc::experimental::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* Channel(
      ::grpc::experimental::CallbackServerContext* /*context*/)
    #endif
      { return nullptr; }
  };
  typedef Service StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef Service StreamedService;
};

}  // namespace v1
}  // namespace multichain


#endif  // GRPC_multichain_2eproto__INCLUDED