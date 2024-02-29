#pragma once

#include <dire/defines.hpp>

namespace dire::detail::system_dirs
{

auto unix_home() -> Optional<Path>;

} // namespace dire::detail::system_dirs
