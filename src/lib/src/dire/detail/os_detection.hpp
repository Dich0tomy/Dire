#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#define DIRE_OS_WINDOWS
#elif defined(__APPLE__)
	#define DIRE_OS_MAC
#elif defined(__linux__)
	#define DIRE_OS_LINUX
#else
	#error "Unknown and unsupported platform"
#endif
