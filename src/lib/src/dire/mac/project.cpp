#include <algorithm>
#include <cassert>

#include <dire/project.hpp>
#include <dire/base.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>
#include <dire/detail/system_dirs/shared.hpp>
#include <dire/detail/getenv.hpp>

namespace dire
{

auto name(std::string domain, std::string org, std::string app_name) -> PlatformProjectName
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

	domain = detail::trim(std::move(domain));
	std::ranges::replace(domain, ' ', '-');

	org = detail::trim(std::move(org));

	app_name = detail::trim(std::move(app_name));
	std::ranges::replace(app_name, ' ', '-');

	return PlatformProjectName(domain + "." + org + "." + app_name);
}

auto ProjectDirsBundle::make(PlatformProjectName project_name) -> Optional<ProjectDirsBundle>
{
	auto home = home_dir();

	if(not home) return {};

	namespace bd = detail;
	using detail::concat_project_path;

	auto config_dir = concat_project_path(bd::config_dir_from_home(*home), std::move(project_name));

	return { {
		.cache_dir = concat_project_path(bd::cache_dir_from_home(*home), std::move(project_name)),
		.config_dir = config_dir,
		.config_local_dir = config_dir,
		.data_dir = config_dir,
		.data_local_dir = config_dir,
		.preference_dir = concat_project_path(bd::preference_dir_from_home(*home), std::move(project_name)),
		.runtime_dir = {},
		.state_dir = {},
	} };
}

auto cache_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return detail::map_project_path(cache_dir(), std::move(project_name));
}

auto config_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return detail::map_project_path(config_dir(), std::move(project_name));
}

auto config_local_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return config_dir(std::move(project_name));
}

auto data_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return config_dir(std::move(project_name));
}

auto data_local_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return config_dir(std::move(project_name));
}

auto preference_dir(PlatformProjectName project_name) -> Optional<Path>
{
	return detail::map_project_path(preference_dir(), std::move(project_name));
}

auto runtime_dir([[maybe_unused]] PlatformProjectName project_name) -> Optional<Path>
{
	return {};
}

auto state_dir([[maybe_unused]] PlatformProjectName project_name) -> Optional<Path>

{
	return {};
}

} // namespace dire
