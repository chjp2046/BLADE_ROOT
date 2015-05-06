// WebSocket, v1.00 2012-09-13
//
// Description: WebSocket FRC6544 codec, written in C++.
// Homepage: http://katzarsky.github.com/WebSocket
// Author: katzarsky@gmail.com

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


enum WebSocketFrameType {
	ERROR_FRAME=0xFF00,
	INCOMPLETE_FRAME=0xFE00,

	OPENING_FRAME=0x3300,
	CLOSING_FRAME=0x3400,

	INCOMPLETE_TEXT_FRAME=0x01,
	INCOMPLETE_BINARY_FRAME=0x02,

	TEXT_FRAME=0x81,
	BINARY_FRAME=0x82,

	PING_FRAME=0x19,
	PONG_FRAME=0x1A
};

class WebSocket
{
	public:

	string resource;
	string host;
	string origin;
	string protocol;
	string key;

	WebSocket();

	/**
	 * @param input_frame .in. pointer to input frame
	 * @param input_len .in. length of input frame
	 * @return [WS_INCOMPLETE_FRAME, WS_ERROR_FRAME, WS_OPENING_FRAME]
	 */
	WebSocketFrameType parseHandshake(unsigned char* input_frame, size_t input_len);
	string answerHandshake();

    WebSocketFrameType makeHandshakeRequest(const std::string& strHost, const std::string strOrigin, const std::string& ws_key, char* out_buffer, size_t out_size, size_t* out_length);

	static size_t makeFrame(WebSocketFrameType frame_type, unsigned char* msg, size_t msg_len, unsigned char* buffer, size_t buffer_len);

	static WebSocketFrameType getFrame(unsigned char* in_buffer, size_t in_length, unsigned char* out_buffer, size_t out_size, size_t* out_length);

    static string trim(string str);
    static vector<string> explode(string theString, string theDelimiter, bool theIncludeEmptyStrings = false );
};

}

#endif	/* WEBSOCKET_H */
