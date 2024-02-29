set(DIRE_SOURCES
	"src/dire/detail/system_dirs/shared.cpp"
	"src/dire/detail/getenv.cpp"

	"src/dire/project.cpp"
)

if(WIN32)
	list(APPEND DIRE_SOURCES
		"src/dire/detail/system_dirs/windows.cpp"

		"src/dire/windows/base.cpp"
		"src/dire/windows/user.cpp"
		"src/dire/windows/project.cpp"
	)
elseif(UNIX AND NOT APPLE)
	list(APPEND DIRE_SOURCES
		"src/dire/detail/system_dirs/xdg_user_dirs.cpp"
		"src/dire/detail/system_dirs/unix_home.cpp"
		"src/dire/detail/system_dirs/linux.cpp"

		"src/dire/linux/base.cpp"
		"src/dire/linux/user.cpp"
		"src/dire/linux/project.cpp"
	)
elseif(UNIX)
	list(APPEND DIRE_SOURCES
		"src/dire/detail/system_dirs/unix_home.cpp"
		"src/dire/detail/system_dirs/mac.cpp"

		"src/dire/mac/base.cpp"
		"src/dire/mac/user.cpp"
		"src/dire/mac/project.cpp"
	)
else()
	message(FATAL_ERROR "Unsupported platform")
endif()

add_library(dire-common INTERFACE)

target_compile_features(dire-common INTERFACE cxx_std_20)

if(WIN32)
	target_compile_definitions(dire-common INTERFACE WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

target_link_libraries(dire-common INTERFACE ctre)

if (DIRE_USE_TL_LIBS)
	target_compile_definitions(dire-common INTERFACE DIRE_USE_TL_LIBS) 
	target_link_libraries(dire-common INTERFACE tl::optional tl::expected)
endif()

add_library(libdire ${DIRE_SOURCES})

target_include_directories(
	libdire
	PUBLIC "include/"
	PRIVATE "src/"
)
target_link_libraries(libdire PRIVATE dire-common)

add_library(_libdire-test-internal ${DIRE_SOURCES})
target_link_libraries(_libdire-test-internal PUBLIC dire-common)

target_include_directories(
	_libdire-test-internal 
	PUBLIC "include/" "src/"
)
