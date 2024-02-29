#include <dire/detail/system_dirs/shared.hpp>

namespace dire::detail::system_dirs
{
auto non_absolute_path_to_none(dire::Path const& path) -> dire::Optional<dire::Path>
{
	if(path.is_absolute()) return path;

	return {};
}

} // namespace dire::detail::system_dirs
