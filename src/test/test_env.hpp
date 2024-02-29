#pragma once

#include <string_view>
#include <cassert>

#include <dire/detail/os_detection.hpp>

#if defined(DIRE_OS_LINUX) || defined(DIRE_OS_MAC)
	#include <cstdlib>
#elif defined(DIRE_OS_WINDOWS)
	#include <windows.h>
#endif

// Yeah it don't really matter it's in a header and stuff, it's a
// simple file for testing purposes

namespace tenv
{

inline auto set(std::string_view name, std::string_view value, bool override = true)
{
#if defined(DIRE_OS_LINUX) || defined(DIRE_OS_MAC)
	assert(setenv(name.data(), value.data(), static_cast<int>(override)) == 0);
#elif defined(DIRE_OS_WINDOWS)
	SetEnvironmentVariable(name.data(), value.data());
#endif
}

inline auto hide(std::string_view name)
{
#if defined(DIRE_OS_LINUX) || defined(DIRE_OS_MAC)
	assert(unsetenv(name.data()) == 0);
#elif defined(DIRE_OS_WINDOWS)
	assert(false); // TODO:
#endif
}

} // namespace tenv
