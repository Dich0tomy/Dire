#include <cassert>

#include <dire/project.hpp>
#include <dire/base.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>
#include <dire/detail/system_dirs/shared.hpp>
#include <dire/detail/getenv.hpp>

namespace
{

auto project_roaming(dire::PlatformProjectName project_name) -> dire::Optional<dire::Path>
{
	using namespace dire::detail;

	return map_project_path(
		system_dirs::known_folder(system_dirs::KnownFolderID::RoamingAppData),
		std::move(project_name)
	);
}

auto project_local(dire::PlatformProjectName project_name) -> dire::Optional<dire::Path>
{
	using namespace dire::detail;

	return map_project_path(
		system_dirs::known_folder(system_dirs::KnownFolderID::LocalAppData),
		std::move(project_name)
	);
}

} // namespace

namespace dire
{

auto name(std::string domain, [[maybe_unused]] std::string org, std::string app_name) -> PlatformProjectName
{
	assert(
		app_name.length() > 0 && "app_name is required to be set. For your own non-cross-platform name, use IReallyWantMyOwnPlatformProjectName"
	);
	assert(
		org.length() > 0 && "org is required to be set. For your own non-cross-platform name, use IReallyWantMyOwnPlatformProjectName"
	);
	assert(
		domain.length() > 1 && "domain is required to be set and bigger in length than 1. For your own non-cross-platform name, use IReallyWantMyOwnPlatformProjectName"
	);

	return PlatformProjectName(
		Path(detail::trim(std::move(org))) / Path(detail::trim(std::move(app_name)))
	);
}

auto ProjectDirsBundle::make(PlatformProjectName project_name) -> Optional<ProjectDirsBundle>
{
	auto data_dir = project_roaming(std::move(project_name));
	auto data_local = project_local(std::move(project_name));

	if(not data_dir or not data_local) {
		return {};
	}

	namespace bd = detail;
	using detail::concat_project_path;

	return { {
		.cache_dir = *data_local / "cache",
		.config_dir = *data_dir / "config",
		.config_local_dir = *data_dir / "config",
		.data_dir = *data_dir / "data",
		.data_local_dir = *data_local / "data",
		.preference_dir = *data_dir / "config",
		.runtime_dir = {},
		.state_dir = {},
	} };
}

auto cache_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return project_local(std::move(project_name)).map([](auto const& path) { return path / "cache"; });
}

auto config_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return project_roaming(std::move(project_name)).map([](auto const& path) { return path / "config"; });
}

auto config_local_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return project_local(std::move(project_name)).map([](auto const& path) { return path / "config"; });
}

auto data_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return project_roaming(std::move(project_name)).map([](auto const& path) { return path / "data"; });
}

auto data_local_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return project_local(std::move(project_name)).map([](auto const& path) { return path / "data"; });
}

auto preference_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return config_dir(std::move(project_name));
}

auto runtime_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return {};
}

auto state_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return {};
}

} // namespace dire
