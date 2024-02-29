#include <string_view>
#include <fstream>
#include <utility>
#include <string>

#include <ctre.hpp>

#include <dire/detail/system_dirs/xdg_user_dirs.hpp>
#include <dire/defines.hpp>

namespace
{

// Oooh scary!
using namespace dire;
using namespace dire::detail;

auto ltrim(std::string str) -> std::string
{
	auto const first_non_white = str.find_first_not_of(" \t");

	if(first_non_white == std::string::npos) return str;

	return str.substr(first_non_white, str.size() - first_non_white);
}

auto rtrim(std::string str) -> std::string
{
	auto const last_non_white_pos = str.find_last_not_of(" \t");

	if(last_non_white_pos == std::string::npos) return str;

	return str.substr(0, last_non_white_pos + 1);
}

auto trim(std::string str) -> std::string
{
	return ltrim(rtrim(std::move(str)));
}

auto is_xdg_key(std::string_view key)
{
	return key.starts_with("XDG_") and key.ends_with("_DIR");
}

auto is_quoted(std::string_view value)
{
	return value.starts_with("\"") and value.ends_with("\"");
}

auto dir_name_from_key(std::string_view key)
{
	using namespace std::string_view_literals;
	static constexpr auto xdg_prefix_len = "XDG_"sv.length();
	static constexpr auto dir_suffix_len = "_DIR"sv.length();

	key.remove_prefix(xdg_prefix_len);
	key.remove_suffix(dir_suffix_len);

	return key;
}

auto unescape(std::string escaped)
{
	for(auto i = 0ull; i < escaped.length(); ++i) {
		if(escaped[i] == '\\') {
			escaped.erase(i, 1);
			i++;
		}
	}

	return escaped;
}

auto unquote(std::string const& quoted)
{
	return quoted.substr(1, quoted.size() - 2);
}

auto parse_xdg_kv_pair(std::string const& line) -> Optional<std::pair<std::string, std::string>>
{
	auto equal_sign_pos = line.find('=');

	if(equal_sign_pos == std::string::npos) return {};

	auto key = rtrim(line.substr(0, equal_sign_pos));

	if(key.empty() or not is_xdg_key(key)) return {};

	auto value = ltrim(line.substr(equal_sign_pos + 1, line.size() - equal_sign_pos + 1));

	if(not is_quoted(value) or value.length() <= 2) return {};

	return { { std::move(key), std::move(value) } };
}

auto parse_xdg_record(Path const& home_dir, std::string line) -> Optional<xdg::DirsMap::value_type>
{
	if(auto kv_pair = parse_xdg_kv_pair(trim(std::move(line)))) {
		auto [key, value] = std::move(*kv_pair);

		key = dir_name_from_key(key);
		value = unquote(unescape(std::move(value)));

		/// If the value is $HOME that means it's disabled
		/// https://www.freedesktop.org/wiki/Software/xdg-user-dirs/
		if(value == "$HOME/" or value == "$HOME") return {};

		if(value.starts_with("$HOME/")) {
			static constexpr auto home_len = std::string_view("$HOME/").length();

			return { { std::move(key), home_dir / value.substr(home_len) } };
		}

		return { { std::move(key), std::move(value) } };
	}

	return {};
}

auto parse_user_dirs(std::istream& content_stream, Path const& home) -> xdg::DirsMap
{
	auto dirs = xdg::DirsMap();

	auto hint = dirs.begin();
	for(auto line = std::string(); std::getline(content_stream, line);) {
		if(auto xdg_record = parse_xdg_record(home, std::move(line))) {
			hint = dirs.emplace_hint(hint, std::move(*xdg_record));
		}
	}

	return dirs;
}

} // namespace

namespace dire::detail::xdg
{

/// Returns a map of all the XDG values from a stream, with XDG_ prefix and _DIR suffix removed
/// e.g. if a file contains
/// ```
/// XDG_DESKTOP_DIR="$HOME/Desktop"
/// XDG_DOWNLOAD_DIR="$HOME/Downloads"
/// ```
/// This returns { { "DESKTOP", "<home>/Desktop"}, { "DOWNLOAD", "<home>/Downloads"} }
/// Where <home> is substituted for the given argument.
///
/// If there are any errors while reading the records it throws them silently away.
auto all_from_stream(std::istream& input, Path const& home) -> DirsMap
{
	return parse_user_dirs(input, home);
}

/// Returns a map of all the XDG values from a file pointed by `user_dir_file`, with XDG_ prefix and _DIR suffix removed
/// e.g. if a file contains
/// ```
/// XDG_DESKTOP_DIR="$HOME/Desktop"
/// XDG_DOWNLOAD_DIR="$HOME/Downloads"
/// ```
/// This returns { { "DESKTOP", "<home>/Desktop"}, { "DOWNLOAD", "<home>/Downloads"} }
/// Where <home> is substituted for the given argument.
///
/// If there are any errors while reading the records it throws them silently away.
auto all_from_file(Path const& user_dir_file, Path const& home) -> DirsMap
{
	auto file = std::ifstream(user_dir_file);
	return all_from_stream(file, home);
}

} // namespace dire::detail::xdg
