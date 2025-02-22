#include <dire/base.hpp>
#include <dire/user.hpp>

#include <dire/detail/system_dirs/system_dirs.hpp>

namespace dire
{

auto UserDirsBundle::make() -> Optional<UserDirsBundle>
{
	auto home = ::dire::home_dir();

	if(not home) {
		return {};
	}

	return UserDirsBundle {
		.audio_dir = *::dire::audio_dir(),
		.desktop_dir = *::dire::desktop_dir(),
		.document_dir = *::dire::document_dir(),
		.download_dir = *::dire::download_dir(),
		.picture_dir = *::dire::picture_dir(),
		.video_dir = *::dire::video_dir(),
		.public_dir = *::dire::public_dir(),

		.font_dir = {},
		.template_dir = *::dire::template_dir(),
	};
}

namespace system_dirs = dire::detail::system_dirs;

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

} // namespace dire
