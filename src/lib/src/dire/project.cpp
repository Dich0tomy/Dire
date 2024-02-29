#include <dire/project.hpp>

#include <dire/defines.hpp>

namespace dire::project::detail
{
auto trim(std::string str) -> std::string
{
	if(str.empty()) return "";

	static constexpr auto whitespace = " \t\r\f\v";

	auto first_non_white = str.find_first_not_of(whitespace);
	auto last_non_white = str.find_last_not_of(whitespace);

	return str.substr(first_non_white, last_non_white - first_non_white + 1);
}

auto concat_project_path(Path const& path, PlatformProjectName project_name) -> Path
{
	return path / static_cast<Path>(std::move(project_name));
}

auto map_project_path(Optional<Path> path, PlatformProjectName project_name) -> Optional<Path>
{
	return path.map([&project_name](auto const& path) {
		return path / static_cast<Path>(std::move(project_name));
	});
}

} // namespace dire::project::detail
