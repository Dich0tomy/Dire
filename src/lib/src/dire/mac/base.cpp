#include <dire/base.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>
#include <dire/detail/system_dirs/shared.hpp>
#include <dire/detail/getenv.hpp>

namespace
{

auto concat_cache_dir(dire::Path const& home) -> dire::Path
{
	return home / "Library" / "Caches";
}

auto concat_config_dir(dire::Path const& home) -> dire::Path
{
	return home / "Library" / "Application Support";
}

auto concat_config_local_dir(dire::Path const& home) -> dire::Path
{
	return concat_config_dir(home);
}

auto concat_data_dir(dire::Path const& home) -> dire::Path
{
	return concat_config_dir(home);
}

auto concat_data_local_dir(dire::Path const& home) -> dire::Path
{
	return concat_config_dir(home);
}

auto concat_preference_dir(dire::Path const& home) -> dire::Path
{
	return home / "Library" / "Preferences";
}

} // namespace

namespace dire::base
{
auto bundle() -> Optional<BaseDirsBundle>
{
	auto home = home_dir();

	if(not home) return {};

	return { {
		.home_dir = *home,
		.cache_dir = concat_cache_dir(*home),
		.config_dir = concat_config_dir(*home),
		.config_local_dir = concat_config_local_dir(*home),
		.data_dir = concat_data_local_dir(*home),
		.data_local_dir = concat_data_dir(*home),
		.preference_dir = concat_preference_dir(*home),
		.executable_dir = {},
		.runtime_dir = {},
		.state_dir = {},
	} };
}

auto home_dir() -> Optional<Path>
{
	return dire::detail::system_dirs::home_dir();
}

auto cache_dir() -> Optional<Path>
{
	return home_dir().map(concat_cache_dir);
}

auto config_dir() -> Optional<Path>
{
	return home_dir().map(concat_config_dir);
}

auto config_local_dir() -> Optional<Path>
{
	return config_dir();
}

auto data_dir() -> Optional<Path>
{
	return config_dir();
}

auto data_local_dir() -> Optional<Path>
{
	return config_dir();
}

auto executable_dir() -> Optional<Path>
{
	return {};
}

auto preference_dir() -> Optional<Path>
{
	return home_dir().map(concat_preference_dir);
}

auto runtime_dir() -> Optional<Path>
{
	return {};
}

auto state_dir() -> Optional<Path>
{
	return {};
}

} // namespace dire::base
