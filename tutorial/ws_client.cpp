#include <folly/io/async/AsyncServerSocket.h>
#include <folly/io/async/AsyncSocket.h>
#include "folly/io/async/AsyncSSLSocket.h"
#include <folly/io/async/AsyncTimeout.h>
#include <folly/io/async/EventBase.h>
#include <folly/SocketAddress.h>
#include <folly/io/IOBuf.h>
#include <boost/scoped_array.hpp>

#include "thirdparty/glog/logging.h"
#include "thirdparty/gflags/gflags.h"
#include <iostream>
#include <signal.h>

#include "WebSocketClient.h"

using namespace boost;
using namespace folly;
using std::string;
using std::vector;
using std::min;
using std::cerr;
using std::endl;
using std::unique_ptr;
using std::chrono::milliseconds;
using boost::scoped_array;

bool bQuit = true;

enum StateEnum {
    STATE_WAITING,
    STATE_SUCCEEDED,
    STATE_FAILED
};

DEFINE_int32(http_port, 11000, "Port to listen on with HTTP protocol");
DEFINE_string(ip, "localhost", "IP/Hostname to bind to");

#if 0
./ws_client --logtostderr=1 --ip=127.0.0.1
#endif

typedef std::function<void()> VoidCallback;

class ConnCallback : public AsyncSocket::ConnectCallback {
public:
    ConnCallback()
        : state(STATE_WAITING)
        , exception(AsyncSocketException::UNKNOWN, "none") {}

    void connectSuccess() noexcept override {
        state = STATE_SUCCEEDED;
        if (successCallback) {
            successCallback();
        }
    }

    void connectErr(const AsyncSocketException& ex) noexcept override {
        state = STATE_FAILED;
        exception = ex;
        if (errorCallback) {
            errorCallback();
        }
    }

    StateEnum state;
    AsyncSocketException exception;
    VoidCallback successCallback;
    VoidCallback errorCallback;
};


class WriteCallback : public AsyncTransportWrapper::WriteCallback {
public:
    WriteCallback()
        : state(STATE_WAITING)
        , bytesWritten(0)
        , exception(AsyncSocketException::UNKNOWN, "none") {}

    void writeSuccess() noexcept override {
        state = STATE_SUCCEEDED;
        if (successCallback) {
            successCallback();
        }
    }

    void myWriteSucessCallback()
    {
        LOG(INFO)<<"write success: "<<bytesWritten;
    }

    void writeErr(size_t bytesWritten,
        const AsyncSocketException& ex) noexcept override {
            state = STATE_FAILED;
            this->bytesWritten = bytesWritten;
            exception = ex;
            if (errorCallback) {
                errorCallback();
            }
    }

    StateEnum state;
    size_t bytesWritten;
    AsyncSocketException exception;
    VoidCallback successCallback;
    VoidCallback errorCallback;
};

WriteCallback wcb;

class ReadCallback : public AsyncTransportWrapper::ReadCallback {
public:
    ReadCallback(folly::AsyncSSLSocket* sock)
        : state(STATE_WAITING)
        , exception(AsyncSocketException::UNKNOWN, "none")
        , buffers() 
        , _socket(sock)
        , iTimes(0) {}

    ~ReadCallback() {
        for (vector<Buffer>::iterator it = buffers.begin();
            it != buffers.end();
            ++it) {
                it->free();
        }
        currentBuffer.free();
    }

    void getReadBuffer(void** bufReturn, size_t* lenReturn) override {
        if (!currentBuffer.buffer) {
            currentBuffer.allocate(4096);
        }
        *bufReturn = currentBuffer.buffer;
        *lenReturn = currentBuffer.length;
    }

    void readDataAvailable(size_t len) noexcept override {
        currentBuffer.length = len;
        buffers.push_back(currentBuffer);
        currentBuffer.reset();
        if (dataAvailableCallback) {
            dataAvailableCallback();
        }        
    }

    void processData()
    {
        std::string strData;

        for (size_t idx = 0; idx < buffers.size(); ++idx) 
        {
            const auto& buf = buffers[idx];
            strData.append(buf.buffer, buf.length);
        }
        
        const char* out_buffer = NULL;
        size_t out_length = 0;
        example::FrameType frame_type = example::WebSocketClient::getFrame(strData.c_str(), strData.size(), &out_buffer, &out_length);
        if (frame_type == example::CONTINUE)
        {
            return;
        }
        

        LOG(INFO)<<"src length:"<<strData.size()<<", frame type:"<<std::hex<<frame_type<<std::dec<<", payload:"<<string(out_buffer, out_length)<<", out_length:"<<out_length;

        buffers.clear();

        if (++iTimes < 100)
        {
            scoped_array<char> buf2(new char[2048]);
            memset(buf2.get(), '\0', 2048);

            std::cout<<"please input text to send to server:"<<std::endl;

            std::string strInput;
            std::cin>>strInput;

            size_t ret_len = example::WebSocketClient::makeFrame(example::TEXT, strInput.c_str(), strInput.size(), buf2.get(), 2048);
            if (ret_len == 0)
            {
                LOG(INFO)<<"error frame";
                _socket->close();
            }
            else
            {
                _socket->write(&wcb, buf2.get(), ret_len);
            }
        }
        else
        {
            _socket->close();
        }
    }

    void readEOF() noexcept override {
        state = STATE_SUCCEEDED;
    }

    void readErr(const AsyncSocketException& ex) noexcept override {
        state = STATE_FAILED;
        exception = ex;
    }

    void verifyData(const char* expected, size_t expectedLen) const {
        size_t offset = 0;
        for (size_t idx = 0; idx < buffers.size(); ++idx) {
            const auto& buf = buffers[idx];
            size_t cmpLen = std::min(buf.length, expectedLen - offset);
            CHECK_EQ(memcmp(buf.buffer, expected + offset, cmpLen), 0);
            CHECK_EQ(cmpLen, buf.length);
            offset += cmpLen;
        }
        CHECK_EQ(offset, expectedLen);
    }

    class Buffer {
    public:
        Buffer() : buffer(nullptr), length(0) {}
        Buffer(char* buf, size_t len) : buffer(buf), length(len) {}

        void reset() {
            buffer = nullptr;
            length = 0;
        }
        void allocate(size_t length) {
            assert(buffer == nullptr);
            this->buffer = static_cast<char*>(malloc(length));
            this->length = length;
        }
        void free() {
            ::free(buffer);
            reset();
        }

        char* buffer;
        size_t length;
    };

    StateEnum state;
    AsyncSocketException exception;
    vector<Buffer> buffers;
    Buffer currentBuffer;
    VoidCallback dataAvailableCallback;
    folly::AsyncSSLSocket* _socket;
    int iTimes;
};

static void SignalIntHandler(int sig)
{
    bQuit = false;
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();

    EventBase evb;

    
    wcb.successCallback = std::bind(&WriteCallback::myWriteSucessCallback, &wcb);
    
    scoped_array<char> buf2(new char[2048]);
    memset(buf2.get(), '\0', 2048);
    size_t iLen = 0;

    example::WebSocketClient ws_codec;
    example::FrameType type = ws_codec.makeHandshakeRequest("127.0.0.1", "", "test_key", buf2.get(), 2048, &iLen);
    if (type == example::ERROR_FRAME)
    {
        LOG(INFO)<<"error frame";
        return 1;
    }

    LOG(INFO)<<"start to connect...";
    google::FlushLogFiles(0);
    
    auto ctx = std::make_shared<SSLContext>();
    folly::AsyncSSLSocket::UniquePtr socket(new folly::AsyncSSLSocket(ctx, &evb));

    ConnCallback ccb;
    ccb.successCallback = [&] { LOG(INFO)<<"connect success, them write["<<iLen<<"]"; socket->write(&wcb, buf2.get(), iLen); };



    folly::SocketAddress addr(FLAGS_ip, FLAGS_http_port);

    socket->connect(&ccb, addr, 1000);

    evb.loop();

    ReadCallback rcb(socket.get());
    rcb.dataAvailableCallback = std::bind(&ReadCallback::processData, &rcb);
    socket->setReadCB(&rcb);

    evb.loop();
}