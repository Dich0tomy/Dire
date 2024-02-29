cmake = import('cmake')

build_type_opts = cmake.subproject_options()
build_type_opts.add_cmake_defines( { 'CMAKE_BUILD_TYPE': get_option('buildtype').to_upper() } )

ctre = dependency('ctre', version: '3.8.1', required: false)
if not ctre.found()
	ctre_sub = cmake.subproject('ctre', options: build_type_opts, required: true)
	message('ctre targets:\n - ' + '\n - '.join(ctre_sub.target_list()))

	ctre = ctre_sub.dependency('ctre')
endif

local_deps = [
	ctre,
]

if(get_option('use_tl_libs'))
	add_project_arguments('-DDIRE_USE_TL_LIBS', language: 'cpp')

	optional = dependency('optional', version: '1.1.0', required: false)
	if not optional.found()
		optional_sub = cmake.subproject('optional', options: build_type_opts, required: true)
		message('optional targets:\n - ' + '\n - '.join(optional_sub.target_list()))

		optional = optional_sub.dependency('optional')
	endif

	expected = dependency('expected', version: '1.1.0', required: false)
	if not expected.found()
		expected_sub = cmake.subproject('expected', options: build_type_opts, required: true)
		message('expected targets:\n - ' + '\n - '.join(expected_sub.target_list()))

		expected = expected_sub.dependency('expected')
	endif

	local_deps += [
		optional,
		expected
	]
endif

compilation_options = [
	'cpp_std=c++20'
]

public_include_dirs = include_directories('include')
private_include_dirs = include_directories('src')

lib_sources = files(
	'src/dire/detail/system_dirs/shared.cpp',
	'src/dire/detail/getenv.cpp',

	'src/dire/project.cpp',
)

os = build_machine.system()

if(os == 'windows')
	lib_sources += [
		'src/dire/windows/base.cpp',
		'src/dire/windows/user.cpp',
		'src/dire/windows/project.cpp',
	]
elif(os in [ 'linux', 'cygwin' ])
	lib_sources += [
		'src/dire/detail/system_dirs/xdg_user_dirs.cpp',
		'src/dire/detail/system_dirs/unix_home.cpp',
		'src/dire/detail/system_dirs/linux.cpp',

		'src/dire/linux/base.cpp',
		'src/dire/linux/user.cpp',
		'src/dire/linux/project.cpp',
	]
elif(os == 'darwin')
	lib_sources += [
		'src/dire/detail/system_dirs/unix_home.cpp',
		'src/dire/detail/system_dirs/mac.cpp',

		'src/dire/mac/base.cpp',
		'src/dire/mac/user.cpp',
		'src/dire/mac/project.cpp',
	]
else
	error('Unsupported platform')
endif

dire_lib = library(
	'dire',
	sources: lib_sources,
	dependencies: local_deps,
	include_directories: [ public_include_dirs, private_include_dirs ],
	override_options: compilation_options,
	install: true
)

dire = declare_dependency(
	link_with: dire_lib,
	include_directories: public_include_dirs,
	dependencies: [ local_deps ]
)

_dire_test_internal = declare_dependency(
	link_with: dire_lib,
	include_directories: [ public_include_dirs, private_include_dirs ],
	dependencies: [ local_deps ]
)
