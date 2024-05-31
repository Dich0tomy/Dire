#pragma once

#include <dire/defines.hpp>

namespace dire::base
{

struct BaseDirsBundle
{
	Path home_dir;
	Path cache_dir;
	Path config_dir;
	Path config_local_dir;
	Path data_dir;
	Path data_local_dir;
	Path preference_dir;

	Optional<Path> executable_dir;
	Optional<Path> runtime_dir;
	Optional<Path> state_dir;
};

auto bundle() -> Optional<BaseDirsBundle>;

auto home_dir() -> Optional<Path>;

auto cache_dir() -> Optional<Path>;
auto config_dir() -> Optional<Path>;
auto config_local_dir() -> Optional<Path>;
auto data_dir() -> Optional<Path>;
auto data_local_dir() -> Optional<Path>;
auto preference_dir() -> Optional<Path>;

auto executable_dir() -> Optional<Path>;
auto runtime_dir() -> Optional<Path>;
auto state_dir() -> Optional<Path>;

namespace detail
{

auto cache_dir_from_home(dire::Path home) -> dire::Path;
auto config_dir_from_home(dire::Path home) -> dire::Path;
auto config_local_dir_from_home(dire::Path home) -> dire::Path;
auto data_dir_from_home(dire::Path home) -> dire::Path;
auto data_local_dir_from_home(dire::Path home) -> dire::Path;
auto executable_dir_from_home(dire::Path home) -> dire::Path;
auto preference_dir_from_home(dire::Path home) -> dire::Path;
auto runtime_dir_from_home(dire::Path home) -> dire::Path;
auto state_dir_from_home(dire::Path home) -> dire::Path;

} // namespace detail

} // namespace dire::base
