#include <dire/base.hpp>
#include <dire/user.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>
#include <dire/detail/system_dirs/shared.hpp>
#include <dire/detail/getenv.hpp>

namespace
{

auto audio_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::detail::system_dirs::user_dirs(home)["MUSIC"];
}

auto desktop_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::detail::system_dirs::user_dirs(home)["DESKTOP"];
}

auto document_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::detail::system_dirs::user_dirs(home)["DOCUMENTS"];
}

auto download_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::detail::system_dirs::user_dirs(home)["DOWNLOAD"];
}

auto font_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::base::detail::data_dir_from_home(home) / "fonts";
}

auto picture_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::detail::system_dirs::user_dirs(home)["PICTURES"];
}

auto public_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::detail::system_dirs::user_dirs(home)["PUBLICSHARE"];
}

auto template_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::detail::system_dirs::user_dirs(home)["TEMPLATES"];
}

auto video_dir_from_home(dire::Path const& home) -> dire::Path
{
	return dire::detail::system_dirs::user_dirs(home)["VIDEOS"];
}

} // namespace

namespace dire::user
{

auto bundle() -> Optional<UserDirsBundle>
{
	auto home = home_dir();

	if(not home) return {};

	return { {
		.home_dir = *home,

		.audio_dir = ::audio_dir_from_home(*home),
		.desktop_dir = ::desktop_dir_from_home(*home),
		.document_dir = ::document_dir_from_home(*home),
		.download_dir = ::download_dir_from_home(*home),
		.picture_dir = ::picture_dir_from_home(*home),
		.video_dir = ::video_dir_from_home(*home),
		.public_dir = ::public_dir_from_home(*home),

		.font_dir = ::font_dir_from_home(*home),
		.template_dir = ::template_dir_from_home(*home),
	} };
}

auto home_dir() -> Optional<Path>
{
	return detail::system_dirs::home_dir();
}

auto audio_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return ::audio_dir_from_home(*home);
	}

	return {};
}

auto desktop_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return ::desktop_dir_from_home(*home);
	}

	return {};
}

auto document_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return ::document_dir_from_home(*home);
	}

	return {};
}

auto download_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return ::download_dir_from_home(*home);
	}

	return {};
}

auto font_dir() -> Optional<Path>
{
	return base::data_dir().map([](auto const& path) { return path / "fonts"; });
}

auto picture_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return ::picture_dir_from_home(*home);
	}

	return {};
}

auto public_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return ::public_dir_from_home(*home);
	}

	return {};
}

auto template_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return ::template_dir_from_home(*home);
	}

	return {};
}

auto video_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return ::video_dir_from_home(*home);
	}

	return {};
}

} // namespace dire::user
