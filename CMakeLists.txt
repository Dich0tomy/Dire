cmake_minimum_required( VERSION 3.5 )

set(CMAKE_CXX_STANDARD 20)

file(READ "./VERSION" DIRE_VERSION)
string(STRIP "${DIRE_VERSION}" DIRE_VERSION) # File reads in the trailing \n

project(
	Dire
	VERSION ${DIRE_VERSION}
	DESCRIPTION "Complete cross-platform solution for data and user directories discovery."
	LANGUAGES CXX
)

if( PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR )
	message( FATAL_ERROR "In-source build is not allowed." )
endif()

set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0077 NEW)

option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile commands" ON)

option(CMAKE_COLOR_DIAGNOSTICS "Color diagnostics" ON)

# Set it as a default
option(DIRE_USE_TL_LIBS "Use TartanLLama's optional and expected" ON)
option(DIRE_BUILD_TESTS "Build tests" OFF)

option(CMAKE_BUILD_TYPE "Default buildtype" "Debug")

message(STATUS "DIRE_USE_TL_LIBS: " ${DIRE_USE_TL_LIBS})
message(STATUS "Color diagnostics: " ${CMAKE_COLOR_DIAGNOSTICS})
message(STATUS "Export compile commands: " ${CMAKE_EXPORT_COMPILE_COMMANDS})

add_subdirectory("external")
add_subdirectory("src")
