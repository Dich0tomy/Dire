#include <string>

#include <dire/detail/getenv.hpp>

#include <dire/defines.hpp>

namespace dire::detail
{

auto getenv(char const* name) -> Optional<std::string>
{
	if(auto* const result = std::getenv(name)) {
		return result;
	}

	return {};
}

} // namespace dire::detail
