#include <dire/defines.hpp>

namespace dire::detail::system_dirs
{

auto non_absolute_path_to_none(Path const& path) -> Optional<dire::Path>;

} // namespace dire::detail::system_dirs
