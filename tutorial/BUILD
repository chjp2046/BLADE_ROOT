cc_binary(
	name = "server",
	srcs = [
		'server.cpp',
		'gen-cpp2/Calculator.cpp',
		'gen-cpp2/calculator_constants.cpp',
		'gen-cpp2/calculator_types.cpp'
	],
	deps = [
		'//thrift/lib/cpp2:thriftcpp2'
	],
	extra_cppflags = [
		'-std=gnu++0x'
	],
    warning = 'no'
)

cc_binary(
	name = "server_proxy",
	srcs = [
		'server_proxy.cpp',
		'gen-cpp2/Calculator.cpp',
        'gen-cpp2/Calculator_client.cpp',
		'gen-cpp2/calculator_constants.cpp',
		'gen-cpp2/calculator_types.cpp'
	],
	deps = [
		'//thrift/lib/cpp2:thriftcpp2'
	],
	extra_cppflags = [
		'-std=gnu++0x'
	],
    warning = 'no'
)

cc_binary(
	name = "client",
	srcs = [
		'client.cpp',
        'gen-cpp2/Calculator_client.cpp',
		'gen-cpp2/Calculator.cpp',
		'gen-cpp2/calculator_constants.cpp',
		'gen-cpp2/calculator_types.cpp'
	],
	deps = [
		'//thrift/lib/cpp2:thriftcpp2'
	],
	extra_cppflags = [
		'-std=gnu++0x'
	],
    warning = 'no'
)


cc_binary(
	name = "echo_server",
	srcs = [
		'EchoHandler.cpp',
	    'EchoServer.cpp',
	],
	deps = [
		'//proxygen/httpserver:proxygenhttpserver'
	],
	extra_cppflags = [
		'-fno-strict-aliasing',
		'-std=gnu++0x',
		'-DLIBMC_FBTRACE_DISABLE',
		'-DHAVE_CONFIG_H',
		'-fPIC',
		'-DPIC'
	],
	warning = 'no'
)


cc_binary(
	name = "ws_client",
	srcs = [
		'ws_client.cpp',
        'WebSocket.cpp'
	],
	deps = [
		'//folly:folly'
	],
	extra_cppflags = [
        '-std=gnu++0x'
	],
    warning = 'no'
)
