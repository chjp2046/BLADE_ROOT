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
