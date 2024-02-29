#pragma once

#include <dire/base.hpp>

#include <dire/defines.hpp>

namespace dire::project
{

class IReallyWantMyOwnPlatformProjectName
{
public:
	explicit IReallyWantMyOwnPlatformProjectName(Path name)
		: name(std::move(name))
	{}

	explicit operator Path const&() const { return name; }

	explicit operator Path() && { return std::move(name); }

private:
	Path name;
};

class PlatformProjectName
{
public:
	PlatformProjectName(IReallyWantMyOwnPlatformProjectName name)
		: name(std::move(name))
	{}

	explicit operator Path const&() const { return name; }

	explicit operator Path() && { return std::move(name); }

private:
	friend auto name(std::string domain, std::string org, std::string app_name) -> PlatformProjectName;

	explicit PlatformProjectName(Path name)
		: name(std::move(name))
	{}

	Path name;
};

struct ProjectDirsBundle
{
	Path cache_dir;
	Path config_dir;
	Path config_local_dir;
	Path data_dir;
	Path data_local_dir;
	Path preference_dir;

	Optional<Path> runtime_dir;
	Optional<Path> state_dir;
};

auto name(std::string domain, std::string org, std::string app_name) -> PlatformProjectName;

auto bundle(PlatformProjectName project_name) -> Optional<ProjectDirsBundle>;

auto cache_dir(PlatformProjectName project_name) -> Optional<Path>;
auto config_dir(PlatformProjectName project_name) -> Optional<Path>;
auto config_local_dir(PlatformProjectName project_name) -> Optional<Path>;
auto data_dir(PlatformProjectName project_name) -> Optional<Path>;
auto data_local_dir(PlatformProjectName project_name) -> Optional<Path>;
auto preference_dir(PlatformProjectName project_name) -> Optional<Path>;
auto runtime_dir(PlatformProjectName project_name) -> Optional<Path>;
auto state_dir(PlatformProjectName project_name) -> Optional<Path>;

namespace detail
{

auto trim(std::string str) -> std::string;

auto concat_project_path(Path const& path, PlatformProjectName project_name) -> Path;

auto map_project_path(Optional<Path> path, PlatformProjectName project_name) -> Optional<Path>;

} // namespace detail

} // namespace dire::project
