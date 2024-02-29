#include <dire/user.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>

namespace dire::user
{

auto bundle() -> Optional<UserDirsBundle>
{
	auto home = home_dir();

	if(not home) {
		return {};
	}

	return { {
		.home_dir = *home,

		.font_dir = {},
		.audio_dir = *audio_dir(),
		.desktop_dir = *desktop_dir(),
		.document_dir = *document_dir(),
		.download_dir = *download_dir(),
		.picture_dir = *picture_dir(),
		.public_dir = *public_dir(),
		.template_dir = *template_dir(),
		.video_dir = *video_dir(),
	} };
}

namespace system_dirs = dire::detail::system_dirs;

auto home_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Profile);
}

auto audio_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Music);
}

auto desktop_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Desktop);
}

auto document_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Documents);
}

auto download_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Downloads);
}

auto font_dir() -> Optional<Path>
{
	// TODO: There probably is a way to figure out a font directory - figure it out
	return {};
}

auto picture_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Pictures);
}

auto public_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Public);
}

auto template_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Templates);
}

auto video_dir() -> Optional<Path>
{
	return system_dirs::known_folder(system_dirs::KnownFolderID::Videos);
}

} // namespace dire::user
