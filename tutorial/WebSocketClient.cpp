#include "WebSocketClient.h"
#include <iostream>
#include <string>
#include <vector>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <arpa/inet.h>

using namespace std;

namespace example
{

#define WEBSOCKET_INITIAL_HEADER_LENGTH 2
#define WEBSOCKET_LEN16_LENGTH 4
#define WEBSOCKET_LEN64_LENGTH 10

#define WEBSOCKET_LEN16_CODE 126
#define WEBSOCKET_LEN64_CODE 127


WebSocketClient::WebSocketClient() {

}


size_t WebSocketClient::makeFrame(FrameType frame_type, char* msg, size_t msg_length, char* buffer, size_t buffer_size)
{
    uint8_t header[10];
    size_t headerLength;
    uint8_t length1;
    if(msg_length <= 125) 
    {
        headerLength = WEBSOCKET_INITIAL_HEADER_LENGTH;
        length1 = (uint8_t)msg_length;
    } else if(msg_length <= 0xffff) {
        headerLength = WEBSOCKET_LEN16_LENGTH;
        length1 = WEBSOCKET_LEN16_CODE;
        *(uint16_t*)&header[2] = htons((uint16_t)msg_length);
    } else {
        headerLength = WEBSOCKET_LEN64_LENGTH;
        length1 = WEBSOCKET_LEN64_CODE;
        *(uint64_t*)&header[2] = htobe64(msg_length);
    }

    header[0] =(uint8_t)( ((1u) << 7) |((uint8_t)(frame_type)&0xf));
    header[1] = length1; //not masked, so just using the value

    if (buffer_size < headerLength + msg_length)
    {
        return 0;
    }
    else
    {
        memcpy(buffer, header, headerLength);
        memcpy(buffer + headerLength, msg, msg_length);
        return headerLength + msg_length;
    }
}

FrameType WebSocketClient::getFrame(unsigned char* in_buffer, size_t in_length, unsigned char* out_buffer, size_t out_size, size_t* out_length)
{
    return TEXT;
}

/*
GET ws://websocket.example.com/ HTTP/1.1
Origin: http://example.com
Connection: Upgrade
Host: websocket.example.com
Upgrade: websocket
Sec-WebSocket-Version: 13
Sec-WebSocket-Key: test_key
*/
FrameType WebSocketClient::makeHandshakeRequest(const std::string& strHost, const std::string strOrigin, const std::string& ws_key,  char* out_buffer, size_t out_size, size_t* out_length)
{
    if (strHost.empty() || ws_key.empty())
    {
        return ERROR;
    }

    this->host = strHost;
    this->origin = origin;
    this->key = ws_key;

    std::string strHeader = "GET ws://";
    strHeader.append(strHost).append(" HTTP/1.1\n");

    if (!strOrigin.empty())
    {
        strHeader.append("Origin: ").append(strOrigin).append("\n");
    }
    strHeader.append("Connection: Upgrade\n");
    strHeader.append("Host: ").append(strHost).append("\n");
    strHeader.append("Upgrade: websocket\n");
    strHeader.append("Sec-WebSocket-Version: 13\n");
    strHeader.append("Sec-WebSocket-Key: ").append(ws_key).append("\r\n\r\n");

    *out_length = snprintf(out_buffer, out_size, "%s", strHeader.c_str());

    return OPENINNG;
}



}