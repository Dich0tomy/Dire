#pragma once

#include <dire/defines.hpp>

namespace dire::detail::system_dirs
{

auto home_dir() -> Optional<Path>;

} // namespace dire::detail::system_dirs
