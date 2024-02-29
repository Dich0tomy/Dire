#include <dire/detail/system_dirs/unix_home.hpp>
#include <dire/detail/system_dirs/mac.hpp>

#include <dire/defines.hpp>
#include <dire/detail/getenv.hpp>

namespace dire::detail::system_dirs
{

auto home_dir() -> Optional<Path>
{
	return unix_home();
}

} // namespace dire::detail::system_dirs
