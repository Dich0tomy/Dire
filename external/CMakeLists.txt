include( FetchContent )

if (DIRE_USE_TL_LIBS)
	FetchContent_Declare(
			optional
			GIT_REPOSITORY https://github.com/TartanLlama/optional.git
			GIT_TAG        v1.1.0
	)

	FetchContent_GetProperties(optional)
	if(NOT optional_POPULATED)
		FetchContent_Populate(optional)
		set(OPTIONAL_BUILD_TESTS OFF CACHE INTERNAL "(Dont build bundled optional tests)")

		add_subdirectory(${optional_SOURCE_DIR} ${optional_BINARY_DIR})
	endif()

	FetchContent_Declare(
		expected
		GIT_REPOSITORY https://github.com/TartanLlama/expected.git
		GIT_TAG        v1.1.0
	)

	FetchContent_GetProperties(expected)
	if(NOT expected_POPULATED)
		FetchContent_Populate(expected)
		set(EXPECTED_BUILD_TESTS OFF CACHE INTERNAL "(Dont build bundled expected tests)")

		add_subdirectory(${expected_SOURCE_DIR} ${expected_BINARY_DIR})
	endif()
endif()

FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0
)
FetchContent_MakeAvailable( catch2 )

FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG 10.1.0
)
FetchContent_MakeAvailable( fmt )

FetchContent_Declare(
	ctre
	GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions
	GIT_TAG v3.8.1
)
FetchContent_MakeAvailable( ctre )
