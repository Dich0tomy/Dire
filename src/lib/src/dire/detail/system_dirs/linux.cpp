#include <dire/detail/system_dirs/xdg_user_dirs.hpp>
#include <dire/detail/system_dirs/unix_home.hpp>
#include <dire/detail/system_dirs/shared.hpp>
#include <dire/detail/system_dirs/linux.hpp>

#include <dire/defines.hpp>
#include <dire/detail/getenv.hpp>

namespace
{
auto user_dirs_filepath(dire::Path const& home) -> dire::Path
{
	auto const fallback_config_dir = home / ".config";

	return dire::detail::getenv("XDG_CONFIG_HOME")
		.and_then(dire::detail::system_dirs::non_absolute_path_to_none)
		.value_or(fallback_config_dir)
		.append("user-dirs.dirs");
}

} // namespace

namespace dire::detail::system_dirs
{

auto home_dir() -> Optional<Path>
{
	return unix_home();
}

auto user_dirs(Path const& home) -> DirsMap
{
	return xdg::all_from_file(user_dirs_filepath(home), home);
}

} // namespace dire::detail::system_dirs
