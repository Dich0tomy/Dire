#include <algorithm>
#include <cassert>

#include <dire/project.hpp>
#include <dire/base.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>
#include <dire/detail/system_dirs/shared.hpp>
#include <dire/detail/getenv.hpp>

namespace dire::project
{

auto name(std::string domain, [[maybe_unused]] std::string org, [[maybe_unused]] std::string app_name) -> PlatformProjectName
{
	assert(
		app_name.length() > 0 && "app_name is required to be set|update. For your own non-cross-platform name, use IReallyWantMyOwnPlatformPojectName"
	);
	assert(
		org.length() > 0 && "org is required to be set|update. For your own non-cross-platform name, use IReallyWantMyOwnPlatformPojectName"
	);
	assert(
		domain.length() > 1 && "domain is required to be set|update. For your own non-cross-platform name, use IReallyWantMyOwnPlatformPojectName"
	);

	app_name = detail::trim(app_name);

	// FIXME: use something that won't suck dick, that is, something that will support actual unicode here
	std::ranges::transform(app_name, app_name.begin(), [](char const c) { return std::tolower(c); });
	std::erase(app_name, ' ');

	return PlatformProjectName(std::move(app_name));
}

auto bundle(PlatformProjectName project_name) -> Optional<ProjectDirsBundle>
{
	auto home = base::home_dir();

	if(not home) return {};

	namespace bd = base::detail;
	using detail::concat_project_path;

	return { {
		.cache_dir = concat_project_path(bd::cache_dir_from_home(*home), std::move(project_name)),
		.config_dir = concat_project_path(bd::config_dir_from_home(*home), std::move(project_name)),
		.config_local_dir = concat_project_path(bd::config_dir_from_home(*home), std::move(project_name)),
		.data_dir = concat_project_path(bd::data_dir_from_home(*home), std::move(project_name)),
		.data_local_dir = concat_project_path(bd::data_dir_from_home(*home), std::move(project_name)),
		.preference_dir = concat_project_path(bd::config_dir_from_home(*home), std::move(project_name)),
		.runtime_dir = base::runtime_dir(),
		.state_dir = concat_project_path(bd::state_dir_from_home(*home), std::move(project_name)),
	} };
}

auto cache_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return detail::map_project_path(base::cache_dir(), std::move(project_name));
}

auto config_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return detail::map_project_path(base::config_dir(), std::move(project_name));
}

auto config_local_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return config_dir(std::move(project_name));
}

auto data_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return detail::map_project_path(base::data_dir(), std::move(project_name));
}

auto data_local_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return data_dir(std::move(project_name));
}

auto preference_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return config_dir(std::move(project_name));
}

auto runtime_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return detail::map_project_path(base::runtime_dir(), std::move(project_name));
}

auto state_dir(PlatformProjectName project_name) -> Optional<Path>

{
	return detail::map_project_path(base::state_dir(), std::move(project_name));
}

} // namespace dire::project
