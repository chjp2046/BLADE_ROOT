/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "Calculator.h"
#include <thrift/lib/cpp/TApplicationException.h>
#include <folly/MoveWrapper.h>
#include <folly/io/IOBuf.h>
#include <folly/io/IOBufQueue.h>
#include <thrift/lib/cpp/transport/THeader.h>
#include <thrift/lib/cpp2/server/Cpp2ConnContext.h>

namespace example { namespace cpp2 {

template <typename ProtocolIn_, typename ProtocolOut_>
void CalculatorAsyncProcessor::_processInThread_add(std::unique_ptr<apache::thrift::ResponseChannel::Request> req, std::unique_ptr<folly::IOBuf> buf, std::unique_ptr<ProtocolIn_> iprot, apache::thrift::Cpp2RequestContext* ctx, apache::thrift::async::TEventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  auto pri = iface_->getRequestPriority(ctx, apache::thrift::concurrency::NORMAL);
  processInThread<ProtocolIn_, ProtocolOut_>(std::move(req), std::move(buf),std::move(iprot), ctx, eb, tm, pri, false, &CalculatorAsyncProcessor::process_add<ProtocolIn_, ProtocolOut_>, this);
}

template <typename ProtocolIn_, typename ProtocolOut_>
void CalculatorAsyncProcessor::process_add(std::unique_ptr<apache::thrift::ResponseChannel::Request> req, std::unique_ptr<folly::IOBuf> buf, std::unique_ptr<ProtocolIn_> iprot,apache::thrift::Cpp2RequestContext* ctx,apache::thrift::async::TEventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  // make sure getConnectionContext is null
  // so async calls don't accidentally use it
  iface_->setConnectionContext(nullptr);
  Calculator_add_pargs args;
  int32_t uarg_num1{0};
  args.num1 = &uarg_num1;
  int32_t uarg_num2{0};
  args.num2 = &uarg_num2;
  std::unique_ptr<apache::thrift::ContextStack> c(this->getContextStack(this->getServiceName(), "Calculator.add", ctx));
  try {
    deserializeRequest(args, buf.get(), iprot.get(), c.get());
  }
  catch (const std::exception& ex) {
    ProtocolOut_ prot;
    if (req) {
      LOG(ERROR) << ex.what() << " in function add";
      apache::thrift::TApplicationException x(apache::thrift::TApplicationException::TApplicationExceptionType::PROTOCOL_ERROR, ex.what());
      folly::IOBufQueue queue = serializeException("add", &prot, iprot->getSeqId(), nullptr, x);
      queue.append(apache::thrift::transport::THeader::transform(queue.move(), ctx->getTransforms(), ctx->getMinCompressBytes()));
      auto queue_mw = folly::makeMoveWrapper(std::move(queue));
      auto req_mw = folly::makeMoveWrapper(std::move(req));
      eb->runInEventBaseThread([=]() mutable {
        (*req_mw)->sendReply(queue_mw->move());
      }
      );
      return;
    }
    else {
      LOG(ERROR) << ex.what() << " in oneway function add";
    }
  }
  auto callback = folly::make_unique<apache::thrift::HandlerCallback<int64_t>>(std::move(req), std::move(c), return_add<ProtocolIn_,ProtocolOut_>, throw_add<ProtocolIn_, ProtocolOut_>, throw_wrapped_add<ProtocolIn_, ProtocolOut_>, iprot->getSeqId(), eb, tm, ctx);
  if (!callback->isRequestActive()) {
    callback.release()->deleteInThread();
    return;
  }
  ctx->setStartedProcessing();
  iface_->async_tm_add(std::move(callback), *args.num1, *args.num2);
}

template <class ProtocolIn_, class ProtocolOut_>
folly::IOBufQueue CalculatorAsyncProcessor::return_add(int32_t protoSeqId, apache::thrift::ContextStack* ctx, int64_t const& _return) {
  ProtocolOut_ prot;
  Calculator_add_presult result;
  result.success = const_cast<int64_t*>(&_return);
  result.__isset.success = true;
  return serializeResponse("add", &prot, protoSeqId, ctx, result);
}

template <class ProtocolIn_, class ProtocolOut_>
void CalculatorAsyncProcessor::throw_add(std::unique_ptr<apache::thrift::ResponseChannel::Request> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,std::exception_ptr ep,apache::thrift::Cpp2RequestContext* reqCtx) {
  ProtocolOut_ prot;
  try {
    std::rethrow_exception(ep);
  }
  catch (const std::exception& e) {
    if (req) {
      LOG(ERROR) << folly::exceptionStr(e).toStdString() << " in function add";
      apache::thrift::TApplicationException x(folly::exceptionStr(e).toStdString());
      ctx->userException(folly::demangle(typeid(e)).toStdString(), e.what());
      folly::IOBufQueue queue = serializeException("add", &prot, protoSeqId, ctx, x);
      queue.append(apache::thrift::transport::THeader::transform(queue.move(), reqCtx->getTransforms(), reqCtx->getMinCompressBytes()));
      req->sendReply(queue.move());
      return;
    }
    else {
      LOG(ERROR) << folly::exceptionStr(e).toStdString() << " in oneway function add";
    }
  }
  catch (...) {
    if (req) {
      LOG(ERROR) << "<unknown exception>" << " in function add";
      apache::thrift::TApplicationException x("<unknown exception>");
      folly::IOBufQueue queue = serializeException("add", &prot, protoSeqId, nullptr, x);
      queue.append(apache::thrift::transport::THeader::transform(queue.move(), reqCtx->getTransforms(), reqCtx->getMinCompressBytes()));
      req->sendReply(queue.move());
      return;
    }
    else {
      LOG(ERROR) << "<unknown exception>" << " in oneway function add";
    }
  }
}

template <class ProtocolIn_, class ProtocolOut_>
void CalculatorAsyncProcessor::throw_wrapped_add(std::unique_ptr<apache::thrift::ResponseChannel::Request> req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx) {
  if (!ew) {
    return;
  }
  ProtocolOut_ prot;
   {
    if (req) {
      LOG(ERROR) << ew.what().toStdString() << " in function add";
      apache::thrift::TApplicationException x(ew.what().toStdString());
      ctx->userException(ew.class_name().toStdString(), ew.what().toStdString());
      folly::IOBufQueue queue = serializeException("add", &prot, protoSeqId, ctx, x);
      queue.append(apache::thrift::transport::THeader::transform(queue.move(), reqCtx->getTransforms(), reqCtx->getMinCompressBytes()));
      req->sendReply(queue.move());
      return;
    }
    else {
      LOG(ERROR) << ew.what().toStdString() << " in oneway function add";
    }
  }
}

template <typename Protocol_>
void CalculatorAsyncClient::addT(Protocol_* prot, apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback, int32_t num1, int32_t num2) {
  std::unique_ptr<apache::thrift::ContextStack> ctx = this->getContextStack(this->getServiceName(), "Calculator.add", connectionContext_.get());
  Calculator_add_pargs args;
  args.num1 = &num1;
  args.num2 = &num2;
  apache::thrift::clientSendT<false>(prot, rpcOptions, std::move(callback), std::move(ctx), channel_.get(), args, "add", [](Protocol_* prot, Calculator_add_pargs& args) { args.write(prot); }, [](Protocol_* prot, Calculator_add_pargs& args) { return args.serializedSizeZC(prot); });
}

template <typename Protocol_>
folly::exception_wrapper CalculatorAsyncClient::recv_wrapped_addT(Protocol_* prot, int64_t& _return, ::apache::thrift::ClientReceiveState& state) {
  if (state.isException()) {
    return state.exceptionWrapper();
  }
  prot->setInput(state.buf());
  auto guard = folly::makeGuard([&] {prot->setInput(nullptr);});
  apache::thrift::ContextStack* ctx = state.ctx();
  std::string fname;
  int32_t protoSeqId = 0;
  apache::thrift::MessageType mtype;
  ctx->preRead();
  folly::exception_wrapper interior_ew;
  auto caught_ew = folly::try_and_catch<apache::thrift::TException, apache::thrift::protocol::TProtocolException>([&]() {
    prot->readMessageBegin(fname, mtype, protoSeqId);
    if (mtype == apache::thrift::T_EXCEPTION) {
      apache::thrift::TApplicationException x;
      x.read(prot);
      prot->readMessageEnd();
      interior_ew = folly::make_exception_wrapper<apache::thrift::TApplicationException>(x);
      return; // from try_and_catch
    }
    if (mtype != apache::thrift::T_REPLY) {
      prot->skip(apache::thrift::protocol::T_STRUCT);
      prot->readMessageEnd();
      interior_ew = folly::make_exception_wrapper<apache::thrift::TApplicationException>(apache::thrift::TApplicationException::TApplicationExceptionType::INVALID_MESSAGE_TYPE);
      return; // from try_and_catch
    }
    if (fname.compare("add") != 0) {
      prot->skip(apache::thrift::protocol::T_STRUCT);
      prot->readMessageEnd();
      interior_ew = folly::make_exception_wrapper<apache::thrift::TApplicationException>(apache::thrift::TApplicationException::TApplicationExceptionType::WRONG_METHOD_NAME);
      return; // from try_and_catch
    }
    ::apache::thrift::SerializedMessage smsg;
    smsg.protocolType = prot->protocolType();
    smsg.buffer = state.buf();
    ctx->onReadData(smsg);
    Calculator_add_presult result;
    result.success = &_return;
    result.read(prot);
    prot->readMessageEnd();
    ctx->postRead(state.buf()->length());
    if (result.__isset.success) {
      // _return pointer has been filled
      return; // from try_and_catch
    }
    else {
      interior_ew = folly::make_exception_wrapper<apache::thrift::TApplicationException>(apache::thrift::TApplicationException::TApplicationExceptionType::MISSING_RESULT, "failed: unknown result");
      return; // from try_and_catch
    }
  }
  );
  if (interior_ew || caught_ew) {
    ctx->handlerError();
    return interior_ew ? interior_ew : caught_ew;
  }
  return folly::exception_wrapper();
}

template <typename Protocol_>
int64_t CalculatorAsyncClient::recv_addT(Protocol_* prot, ::apache::thrift::ClientReceiveState& state) {
  int64_t _return;
  auto ew = recv_wrapped_addT(prot, _return, state);
  if (ew) {
    ew.throwException();
  }
  return _return;
}

template <class Protocol_>
uint32_t Calculator_add_pargs::read(Protocol_* iprot) {
  uint32_t xfer = 0;
  std::string fname;
  apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using apache::thrift::TProtocolException;


  while (true) {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == apache::thrift::protocol::T_STOP) {
      break;
    }
    if (fid == std::numeric_limits<int16_t>::min()) {
      if (fname == "num1") {
        fid = 1;
        ftype = apache::thrift::protocol::T_I32;
      }
      else if (fname == "num2") {
        fid = 2;
        ftype = apache::thrift::protocol::T_I32;
      }
    }
    switch (fid) {
      case 1:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32((*const_cast<int32_t*>(this->num1)));
          this->__isset.num1 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 2:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32((*const_cast<int32_t*>(this->num2)));
          this->__isset.num2 = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      default:
      {
        xfer += iprot->skip(ftype);
        break;
      }
    }
    xfer += iprot->readFieldEnd();
  }
  xfer += iprot->readStructEnd();

  return xfer;
}

template <class Protocol_>
uint32_t Calculator_add_pargs::serializedSize(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Calculator_add_pargs");
  xfer += prot_->serializedFieldSize("num1", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32((*const_cast<int32_t*>(this->num1)));
  xfer += prot_->serializedFieldSize("num2", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->serializedSizeI32((*const_cast<int32_t*>(this->num2)));
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Calculator_add_pargs::serializedSizeZC(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Calculator_add_pargs");
  xfer += prot_->serializedFieldSize("num1", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->serializedSizeI32((*const_cast<int32_t*>(this->num1)));
  xfer += prot_->serializedFieldSize("num2", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->serializedSizeI32((*const_cast<int32_t*>(this->num2)));
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Calculator_add_pargs::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("Calculator_add_pargs");
  xfer += prot_->writeFieldBegin("num1", apache::thrift::protocol::T_I32, 1);
  xfer += prot_->writeI32((*const_cast<int32_t*>(this->num1)));
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("num2", apache::thrift::protocol::T_I32, 2);
  xfer += prot_->writeI32((*const_cast<int32_t*>(this->num2)));
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

template <class Protocol_>
uint32_t Calculator_add_presult::read(Protocol_* iprot) {
  uint32_t xfer = 0;
  std::string fname;
  apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using apache::thrift::TProtocolException;


  while (true) {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == apache::thrift::protocol::T_STOP) {
      break;
    }
    if (fid == std::numeric_limits<int16_t>::min()) {
      if (fname == "success") {
        fid = 0;
        ftype = apache::thrift::protocol::T_I64;
      }
    }
    switch (fid) {
      case 0:
      {
        if (ftype == apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64((*const_cast<int64_t*>(this->success)));
          this->__isset.success = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      default:
      {
        xfer += iprot->skip(ftype);
        break;
      }
    }
    xfer += iprot->readFieldEnd();
  }
  xfer += iprot->readStructEnd();

  return xfer;
}

template <class Protocol_>
uint32_t Calculator_add_presult::serializedSize(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Calculator_add_presult");
  if (this->__isset.success) {
    xfer += prot_->serializedFieldSize("success", apache::thrift::protocol::T_I64, 0);
    xfer += prot_->serializedSizeI64((*const_cast<int64_t*>(this->success)));
  }
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Calculator_add_presult::serializedSizeZC(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Calculator_add_presult");
  if (this->__isset.success) {
    xfer += prot_->serializedFieldSize("success", apache::thrift::protocol::T_I64, 0);
    xfer += prot_->serializedSizeI64((*const_cast<int64_t*>(this->success)));
  }
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Calculator_add_presult::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("Calculator_add_presult");
  if (this->__isset.success) {
    xfer += prot_->writeFieldBegin("success", apache::thrift::protocol::T_I64, 0);
    xfer += prot_->writeI64((*const_cast<int64_t*>(this->success)));
    xfer += prot_->writeFieldEnd();
  }
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

}} // example::cpp2
namespace apache { namespace thrift {

}} // apache::thrift