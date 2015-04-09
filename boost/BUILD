cc_library(
	name = "boost_system",
	prebuilt = 1,
	export_incs = '.'
)

cc_library(
	name = "boost_thread",
	prebuilt = 1,
	deps = [
		':boost_system',
	],
	export_incs = '.'
)

cc_library(
	name = "boost_filesystem",
	prebuilt = 1,
	deps = [
		':boost_system',
	],
	export_incs = '.'
)

cc_library(
	name = "boost_regex",
	prebuilt = 1,
	export_incs = '.'
)