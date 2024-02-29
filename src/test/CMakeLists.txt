set(TEST_SOURCES "test_main.cpp")

if(WIN32)
	list(APPEND TEST_SOURCES
		"windows/project_dirs.cpp"
		"windows/user_dirs.cpp"
	)
elseif(UNIX AND NOT APPLE)
	list(APPEND TEST_SOURCES
		"xdg_user_dirs.cpp"
		"linux/base_dirs.cpp"
		"linux/user_dirs.cpp"
		"linux/project_dirs.cpp"
	)
elseif(UNIX)
	list(APPEND TEST_SOURCES
		"mac/base_dirs.cpp"
		"mac/project_dirs.cpp"
		"mac/user_dirs.cpp"
	)
else()
	message(FATAL_ERROR "Unsupported platform")
endif()

add_executable(dire_test ${TEST_SOURCES})

target_compile_features(dire_test INTERFACE cxx_std_20)

target_include_directories(dire_test PRIVATE ".")

target_link_libraries(dire_test PRIVATE Catch2 _libdire-test-internal)
