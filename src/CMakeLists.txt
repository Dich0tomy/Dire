add_subdirectory("lib")
add_subdirectory("app")

if(DIRE_BUILD_TESTS)
	add_subdirectory("test")
endif()
