#include <vector>

#include <dire/detail/system_dirs/xdg_user_dirs.hpp>
#include <dire/detail/system_dirs/linux.hpp>

#include <dire/detail/getenv.hpp>
#include <dire/defines.hpp>

#include <unistd.h>
#include <pwd.h>

namespace
{

auto fallback_to_pwuid() -> dire::Optional<dire::Path>
{
	auto pwuid_buffer_size = sysconf(_SC_GETPW_R_SIZE_MAX);
	if(pwuid_buffer_size == -1) {
		// NOTE: We really don't need more than ~64, the username length limit is 32,
		// but if someone decides they wanna mount their home into /i-really-like-long-names/this-is-my-home-yippie
		// we want to support that
		pwuid_buffer_size = 128;
	}

	auto buffer = std::vector<char>(pwuid_buffer_size);

	auto record = passwd();
	passwd* result = nullptr;

	if(getpwuid_r(getuid(), &record, buffer.data(), buffer.size(), &result) != 0) {
		// The user doesn't have a home directory
		if(not result->pw_dir) return {};
		return result->pw_dir;
	}

	return {};
}

auto discard_empty_home(dire::Path home) -> dire::Optional<dire::Path>
{
	if(home.empty()) return {};

	return home;
}

} // namespace

namespace dire::detail::system_dirs
{

auto unix_home() -> Optional<Path>
{
	return getenv("HOME")
		.and_then(discard_empty_home)
		.or_else(fallback_to_pwuid);
}

} // namespace dire::detail::system_dirs
