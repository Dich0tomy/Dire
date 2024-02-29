#pragma once

#include <string>

#include <dire/defines.hpp>

namespace dire::detail
{

auto getenv(char const* name) -> Optional<std::string>;

} // namespace dire::detail
