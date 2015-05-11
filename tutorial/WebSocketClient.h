#ifndef WEBSOCKET_H
#define	WEBSOCKET_H

#include <assert.h>
#include <stdint.h> /* uint8_t */
#include <stdio.h> /* sscanf */
#include <ctype.h> /* isdigit */
#include <stddef.h> /* int */

// std c++
#include <vector> 
#include <string> 

using namespace std;

namespace example
{


enum FrameType 
{
    OPENINNG = 0xAA,
    CONTINUE = 0x00,
    TEXT = 0x01,
    BINARY = 0x02,
    CLOSE = 0x08,
    PING = 0x09,
    PONG = 0x0A,
    ERROR_FRAME = 0x5A
};

class WebSocketClient
{
	public:

	string resource;
	string host;
	string origin;
	string protocol;
	string key;

	WebSocketClient();

    FrameType makeHandshakeRequest(const std::string& strHost, const std::string strOrigin, const std::string& ws_key, char* out_buffer, size_t out_size, size_t* out_length);

	static size_t makeFrame(FrameType frame_type, const char* msg, size_t msg_len, char* buffer, size_t buffer_len);

	static FrameType getFrame(const char* in_buffer, size_t in_length, const char** out_buffer, size_t* out_length);
};

}

#endif	/* WEBSOCKET_H */
