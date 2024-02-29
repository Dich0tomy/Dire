#pragma once

#include <dire/detail/os_detection.hpp>

#if defined(DIRE_OS_LINUX)

	#include <dire/detail/system_dirs/linux.hpp>

#elif defined(DIRE_OS_WINDOWS)

	#include <dire/detail/system_dirs/windows.hpp>

#elif defined(DIRE_OS_MAC)

	#include <dire/detail/system_dirs/mac.hpp>

#endif
