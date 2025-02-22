#include <dire/base.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>

namespace dire
{

auto BaseDirsBundle::make() -> Optional<BaseDirsBundle>
{
	auto home = ::dire::home_dir();
	auto data = ::dire::data_dir();
	auto data_local = ::dire::data_local_dir();

	if(not home or not data or not data_local) {
		return {};
	}

	return BaseDirsBundle {
		.home_dir = *home,
		.cache_dir = *data_local,
		.config_dir = *data,
		.config_local_dir = *data_local,
		.data_dir = *data,
		.data_local_dir = *data_local,
		.preference_dir = *data,
		.executable_dir = {},
		.runtime_dir = {},
		.state_dir = {},
	};
}

namespace system_dirs = dire::detail::system_dirs;

auto home_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Profile);
}

auto data_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::RoamingAppData);
}

auto data_local_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::LocalAppData);
}

auto cache_dir() -> Optional<Path>
{
	return data_local_dir();
}

auto config_dir() -> Optional<Path>
{
	return data_dir();
}

auto config_local_dir() -> Optional<Path>
{
	return data_local_dir();
}

auto executable_dir() -> Optional<Path>
{
	return {};
}

auto preference_dir() -> Optional<Path>
{
	return data_dir();
}

auto runtime_dir() -> Optional<Path>
{
	return {};
}

auto state_dir() -> Optional<Path>
{
	return {};
}

} // namespace dire
