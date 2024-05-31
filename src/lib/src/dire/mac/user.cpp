#include <dire/base.hpp>
#include <dire/user.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>
#include <dire/detail/system_dirs/shared.hpp>
#include <dire/detail/getenv.hpp>

namespace
{

auto concat_audio_dir(dire::Path const& home) -> dire::Path
{
	return home / "Music";
}

auto concat_desktop_dir(dire::Path const& home) -> dire::Path
{
	return home / "Desktop";
}

auto concat_document_dir(dire::Path const& home) -> dire::Path
{
	return home / "Documents";
}

auto concat_download_dir(dire::Path const& home) -> dire::Path
{
	return home / "Downloads";
}

auto concat_font_dir(dire::Path const& home) -> dire::Path
{
	return home / "Library" / "Fonts";
}

auto concat_picture_dir(dire::Path const& home) -> dire::Path
{
	return home / "Pictures";
}

auto concat_public_dir(dire::Path const& home) -> dire::Path
{
	return home / "Public";
}

auto concat_video_dir(dire::Path const& home) -> dire::Path
{
	return home / "Movies";
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

		.audio_dir = concat_audio_dir(*home),
		.desktop_dir = concat_desktop_dir(*home),
		.document_dir = concat_document_dir(*home),
		.download_dir = concat_download_dir(*home),
		.picture_dir = concat_picture_dir(*home),
		.video_dir = concat_video_dir(*home),
		.public_dir = concat_public_dir(*home),

		.font_dir = concat_font_dir(*home),
		.template_dir = {},
	} };
}

auto home_dir() -> Optional<Path>
{
	return detail::system_dirs::home_dir();
}

auto audio_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return concat_audio_dir(*home);
	}

	return {};
}

auto desktop_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return concat_desktop_dir(*home);
	}

	return {};
}

auto document_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return concat_document_dir(*home);
	}

	return {};
}

auto download_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return concat_download_dir(*home);
	}

	return {};
}

auto font_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return concat_font_dir(*home);
	}

	return {};
}

auto picture_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return concat_picture_dir(*home);
	}

	return {};
}

auto public_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return concat_public_dir(*home);
	}

	return {};
}

auto template_dir() -> Optional<Path>
{
	return {};
}

auto video_dir() -> Optional<Path>
{
	if(auto home = home_dir()) {
		return concat_video_dir(*home);
	}

	return {};
}

} // namespace dire::user
