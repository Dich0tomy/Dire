#pragma once

#include <dire/detail/system_dirs/xdg_user_dirs.hpp>
#include <dire/defines.hpp>

namespace dire::detail::system_dirs
{

using DirsMap = xdg::DirsMap;

auto home_dir() -> Optional<Path>;

auto user_dirs(Path const& home) -> DirsMap;

} // namespace dire::detail::system_dirs
