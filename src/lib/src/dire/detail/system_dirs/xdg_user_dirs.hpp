#pragma once

#include <unordered_map>

#include <dire/defines.hpp>

namespace dire::detail::xdg
{

using DirsMap = std::unordered_map<std::string, Path>;

auto all_from_file(Path const& user_dir_file, Path const& home) -> DirsMap;
auto all_from_stream(std::istream& input, Path const& home) -> DirsMap;

} // namespace dire::detail::xdg
