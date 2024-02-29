#pragma once

// This is intentionally a transitive include

#include <filesystem>

#if defined(DIRE_USE_TL_LIBS)
	#include <tl/optional.hpp>
#else
	#include <optional>
#endif

namespace dire
{

using Path = std::filesystem::path;

#if defined(DIRE_USE_TL_LIBS)

template<typename T>
using Optional = tl::optional<T>;

#else

template<typename T>
using Optional = std::optional<T>;

#endif

} // namespace dire
