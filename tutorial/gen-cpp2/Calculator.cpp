/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "Calculator.h"

#include "Calculator.tcc"

#include <thrift/lib/cpp2/protocol/Protocol.h>
#include <thrift/lib/cpp2/protocol/BinaryProtocol.h>
#include <thrift/lib/cpp2/protocol/CompactProtocol.h>
namespace example { namespace cpp2 {

std::unique_ptr<apache::thrift::AsyncProcessor> CalculatorSvIf::getProcessor() {
  return std::unique_ptr<apache::thrift::AsyncProcessor>(new CalculatorAsyncProcessor((CalculatorSvIf*)this));
}

int64_t CalculatorSvIf::add(int32_t num1, int32_t num2) {
  throw apache::thrift::TApplicationException("Function add is unimplemented");
  return 0;
}

folly::Future<int64_t> CalculatorSvIf::future_add(int32_t num1, int32_t num2) {
  folly::Promise<int64_t> promise0;
  try {
    promise0.setValue(add(num1, num2));
  } catch(const std::exception& ex) {
    promise0.setException(folly::exception_wrapper(std::current_exception()));
  }
  return promise0.getFuture();
}

void CalculatorSvIf::async_tm_add(std::unique_ptr<apache::thrift::HandlerCallback<int64_t>> callback, int32_t num1, int32_t num2) {
  auto callbackp = callback.release();
  setEventBase(callbackp->getEventBase());
  setThreadManager(callbackp->getThreadManager());
  setConnectionContext(callbackp->getConnectionContext());
  try {
    auto future1 = future_add(num1, num2);
    future1.then([=](folly::Try<int64_t>&& _return) {
      try {
        callbackp->resultInThread(std::move(_return.value()));
      } catch(...) {
        callbackp->exceptionInThread(std::current_exception());
      }
    }
    );
  } catch(const std::exception& ex) {
    callbackp->exceptionInThread(std::current_exception());
  }
}

int64_t CalculatorSvNull::add(int32_t num1, int32_t num2) {
  return 0;
}

const char* CalculatorAsyncProcessor::getServiceName() {
  return "Calculator";
}

folly::Optional<std::string> CalculatorAsyncProcessor::getCacheKey(folly::IOBuf* buf, apache::thrift::protocol::PROTOCOL_TYPES protType) {
  std::string fname;
  apache::thrift::MessageType mtype;
  int32_t protoSeqId = 0;
  std::string pname;
  apache::thrift::protocol::TType ftype;
  int16_t fid;
  try {
    switch(protType) {
      case apache::thrift::protocol::T_BINARY_PROTOCOL:
      {
        std::unique_ptr<apache::thrift::BinaryProtocolReader> iprot(new apache::thrift::BinaryProtocolReader());
        iprot->setInput(buf);
        iprot->readMessageBegin(fname, mtype, protoSeqId);
        auto pfn = CacheKeyMap.find(fname);
        if (pfn == CacheKeyMap.end()) {
          return folly::none;
        }
        auto cacheKeyParamId = pfn->second;
        uint32_t xfer = 0;
        xfer += iprot->readStructBegin(pname);
        while(true) {
          xfer += iprot->readFieldBegin(pname, ftype, fid);
          if (ftype == apache::thrift::protocol::T_STOP) {
            break;
          }
          if (fid == cacheKeyParamId) {
            std::string cacheKey;
            iprot->readString(cacheKey);
            return folly::Optional<std::string>(std::move(cacheKey));
          }
          xfer += iprot->skip(ftype);
          xfer += iprot->readFieldEnd();
        }
        return folly::none;
      }
      case apache::thrift::protocol::T_COMPACT_PROTOCOL:
      {
        std::unique_ptr<apache::thrift::CompactProtocolReader> iprot(new apache::thrift::CompactProtocolReader());
        iprot->setInput(buf);
        iprot->readMessageBegin(fname, mtype, protoSeqId);
        auto pfn = CacheKeyMap.find(fname);
        if (pfn == CacheKeyMap.end()) {
          return folly::none;
        }
        auto cacheKeyParamId = pfn->second;
        uint32_t xfer = 0;
        xfer += iprot->readStructBegin(pname);
        while(true) {
          xfer += iprot->readFieldBegin(pname, ftype, fid);
          if (ftype == apache::thrift::protocol::T_STOP) {
            break;
          }
          if (fid == cacheKeyParamId) {
            std::string cacheKey;
            iprot->readString(cacheKey);
            return folly::Optional<std::string>(std::move(cacheKey));
          }
          xfer += iprot->skip(ftype);
          xfer += iprot->readFieldEnd();
        }
        return folly::none;
      }
      default:
      {
        return folly::none;
        break;
      }
    }
  } catch(const std::exception& e) {
    LOG(ERROR) << "Caught an exception parsing buffer:" << e.what();
    return folly::none;
  }
  return folly::none;
}

void CalculatorAsyncProcessor::process(std::unique_ptr<apache::thrift::ResponseChannel::Request> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::protocol::PROTOCOL_TYPES protType,apache::thrift::Cpp2RequestContext* context,apache::thrift::async::TEventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  std::string fname;
  apache::thrift::MessageType mtype;
  int32_t protoSeqId = 0;
  switch(protType) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      std::unique_ptr<apache::thrift::BinaryProtocolReader> iprot(new apache::thrift::BinaryProtocolReader());
      iprot->setInput(buf.get());
      try {
        iprot->readMessageBegin(fname, mtype, protoSeqId);
      } catch(const apache::thrift::TException& ex) {
        LOG(ERROR) << "received invalid message from client: " << ex.what();
        apache::thrift::BinaryProtocolWriter prot;
        if (req) {
          LOG(ERROR) << "invalid message from client" << " in function process";
          apache::thrift::TApplicationException x("invalid message from client");
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << "invalid message from client" << " in oneway function process";
        }
        return;
      }
      if (mtype != apache::thrift::T_CALL && mtype != apache::thrift::T_ONEWAY) {
        LOG(ERROR) << "received invalid message of type " << mtype;
        apache::thrift::BinaryProtocolWriter prot;
        if (req) {
          LOG(ERROR) << "invalid message arguments" << " in function process";
          apache::thrift::TApplicationException x("invalid message arguments");
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << "invalid message arguments" << " in oneway function process";
        }
      }
      auto pfn = binaryProcessMap_.find(fname);
      if (pfn == binaryProcessMap_.end()) {
        const std::string exMsg = folly::stringPrintf( "Method name %s not found", fname.c_str());
        apache::thrift::BinaryProtocolWriter prot;
        if (req) {
          LOG(ERROR) << exMsg << " in function process";
          apache::thrift::TApplicationException x(exMsg);
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << exMsg << " in oneway function process";
        }
        return;
      }
      (this->*(pfn->second))(std::move(req), std::move(buf), std::move(iprot), context, eb, tm);
      return;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      std::unique_ptr<apache::thrift::CompactProtocolReader> iprot(new apache::thrift::CompactProtocolReader());
      iprot->setInput(buf.get());
      try {
        iprot->readMessageBegin(fname, mtype, protoSeqId);
      } catch(const apache::thrift::TException& ex) {
        LOG(ERROR) << "received invalid message from client: " << ex.what();
        apache::thrift::CompactProtocolWriter prot;
        if (req) {
          LOG(ERROR) << "invalid message from client" << " in function process";
          apache::thrift::TApplicationException x("invalid message from client");
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << "invalid message from client" << " in oneway function process";
        }
        return;
      }
      if (mtype != apache::thrift::T_CALL && mtype != apache::thrift::T_ONEWAY) {
        LOG(ERROR) << "received invalid message of type " << mtype;
        apache::thrift::CompactProtocolWriter prot;
        if (req) {
          LOG(ERROR) << "invalid message arguments" << " in function process";
          apache::thrift::TApplicationException x("invalid message arguments");
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << "invalid message arguments" << " in oneway function process";
        }
      }
      auto pfn = compactProcessMap_.find(fname);
      if (pfn == compactProcessMap_.end()) {
        const std::string exMsg = folly::stringPrintf( "Method name %s not found", fname.c_str());
        apache::thrift::CompactProtocolWriter prot;
        if (req) {
          LOG(ERROR) << exMsg << " in function process";
          apache::thrift::TApplicationException x(exMsg);
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << exMsg << " in oneway function process";
        }
        return;
      }
      (this->*(pfn->second))(std::move(req), std::move(buf), std::move(iprot), context, eb, tm);
      return;
    }
    default:
    {
      LOG(ERROR) << "invalid protType: " << protType;
      return;
      break;
    }
  }
}

bool CalculatorAsyncProcessor::isOnewayMethod(const folly::IOBuf* buf, const apache::thrift::transport::THeader* header) {
  std::string fname;
  apache::thrift::MessageType mtype;
  int32_t protoSeqId = 0;
  apache::thrift::protocol::PROTOCOL_TYPES protType = static_cast<apache::thrift::protocol::PROTOCOL_TYPES>(header->getProtocolId());
  switch(protType) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader iprot;
      iprot.setInput(buf);
      try {
        iprot.readMessageBegin(fname, mtype, protoSeqId);
        auto it = onewayMethods.find(fname);
        return it != onewayMethods.end();
      } catch(const apache::thrift::TException& ex) {
        LOG(ERROR) << "received invalid message from client: " << ex.what();
        return false;
      }
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader iprot;
      iprot.setInput(buf);
      try {
        iprot.readMessageBegin(fname, mtype, protoSeqId);
        auto it = onewayMethods.find(fname);
        return it != onewayMethods.end();
      } catch(const apache::thrift::TException& ex) {
        LOG(ERROR) << "received invalid message from client: " << ex.what();
        return false;
      }
    }
    default:
    {
      LOG(ERROR) << "invalid protType: " << protType;
      break;
    }
  }
  return false;
}

std::unordered_set<std::string> CalculatorAsyncProcessor::onewayMethods {};
std::unordered_map<std::string, int16_t> CalculatorAsyncProcessor::CacheKeyMap {};
CalculatorAsyncProcessor::binaryProcessMap CalculatorAsyncProcessor::binaryProcessMap_ {
  {"add", &CalculatorAsyncProcessor::_processInThread_add<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}
};
CalculatorAsyncProcessor::compactProcessMap CalculatorAsyncProcessor::compactProcessMap_ {
  {"add", &CalculatorAsyncProcessor::_processInThread_add<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>}
};

}} // example::cpp2
namespace apache { namespace thrift {

}} // apache::thrift