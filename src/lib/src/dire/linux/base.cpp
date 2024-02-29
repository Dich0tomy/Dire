#include <dire/base.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>
#include <dire/detail/system_dirs/shared.hpp>
#include <dire/detail/getenv.hpp>

namespace dire::base
{

namespace detail
{
auto cache_dir_from_home(dire::Path home) -> dire::Path
{
	return dire::detail::getenv("XDG_CACHE_HOME")
		.and_then(dire::detail::system_dirs::non_absolute_path_to_none)
		.value_or(home.append(".cache"));
}

auto config_dir_from_home(dire::Path home) -> dire::Path
{
	return dire::detail::getenv("XDG_CONFIG_HOME")
		.and_then(dire::detail::system_dirs::non_absolute_path_to_none)
		.value_or(home.append(".config"));
}

auto executable_dir_from_home(dire::Path home) -> dire::Path
{
	// WARNING: this is not officially supported by the xdg spec
	return dire::detail::getenv("XDG_BIN_HOME")
		.and_then(dire::detail::system_dirs::non_absolute_path_to_none)
		.value_or(home.append(".local/bin"));
}

auto state_dir_from_home(dire::Path home) -> dire::Path
{
	return dire::detail::getenv("XDG_STATE_HOME")
		.and_then(dire::detail::system_dirs::non_absolute_path_to_none)
		.value_or(home.append(".local/state"));
}

auto data_dir_from_home(dire::Path home) -> dire::Path
{
	return dire::detail::getenv("XDG_DATA_HOME")
		.and_then(dire::detail::system_dirs::non_absolute_path_to_none)
		.value_or(home.append(".local/share"));
}

} // namespace detail

auto bundle() -> Optional<BaseDirsBundle>
{
	auto home = home_dir();

	if(not home) return {};

	return { {
		.home_dir = *home,
		.cache_dir = detail::cache_dir_from_home(*home),
		.config_dir = detail::config_dir_from_home(*home),
		.config_local_dir = detail::config_dir_from_home(*home),
		.data_dir = detail::data_dir_from_home(*home),
		.data_local_dir = detail::data_dir_from_home(*home),
		.preference_dir = detail::config_dir_from_home(*home),
		.executable_dir = detail::executable_dir_from_home(*home),
		.runtime_dir = runtime_dir(),
		.state_dir = detail::state_dir_from_home(*home),
	} };
}

auto home_dir() -> Optional<Path>
{
	return dire::detail::system_dirs::home_dir();
}

auto cache_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return detail::cache_dir_from_home(std::move(*home));
	}

	return {};
}

auto config_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return detail::config_dir_from_home(std::move(*home));
	}

	return {};
}

auto config_local_dir() -> Optional<Path>
{
	return config_dir();
}

auto data_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return detail::data_dir_from_home(std::move(*home));
	}

	return {};
}

auto data_local_dir() -> Optional<Path>
{
	return data_dir();
}

auto executable_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return detail::executable_dir_from_home(std::move(*home));
	}

	return {};
}

auto preference_dir() -> Optional<Path>
{
	return config_dir();
}

auto runtime_dir() -> Optional<Path>
{
	return dire::detail::getenv("XDG_RUNTIME_DIR")
		.and_then(dire::detail::system_dirs::non_absolute_path_to_none);
}

auto state_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return detail::state_dir_from_home(std::move(*home));
	}

	return {};
}

} // namespace dire::base
