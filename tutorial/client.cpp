#include "gen-cpp2/Calculator.h" // From generated code
#include <iostream>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::async;
using namespace example::cpp2;
using namespace folly::wangle;

int main()
{
	TEventBase base;
	int port = 8081; //The port on which server is listening

	// Create a async client socket and connect it. Change
	// the ip address to where the server is listening
	std::shared_ptr<TAsyncSocket> socket(
		TAsyncSocket::newSocket(&base, "127.0.0.1", port));

	// Create a HeaderClientChannel object which is used in creating
	// client object
	auto client_channel = HeaderClientChannel::newChannel(socket);
	// Create a client object
	CalculatorAsyncClient client(std::move(client_channel));
	// Invoke the add function on server. As we are doing async
	// invocation of the function, we do not immediately get
	// the result. Instead we get a future object.
	folly::Future<int64_t> f = client.future_add(2, 3);
	// Set the callback on the future object. The callback is called
	// when the result is received from server
	f.then(
		[](folly::Try<int64_t>&& t) {
			// We received the result from server
			cout << "result = " << t.value() << endl;
	});
	base.loop();
}
