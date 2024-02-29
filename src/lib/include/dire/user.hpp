#pragma once

#include <dire/defines.hpp>

namespace dire::user
{

struct UserDirsBundle
{
	Path home_dir;

	Optional<Path> font_dir;
	Path audio_dir;
	Path desktop_dir;
	Path document_dir;
	Path download_dir;
	Path picture_dir;
	Path public_dir;
	Path template_dir;
	Path video_dir;
};

auto bundle() -> Optional<UserDirsBundle>;

auto home_dir() -> Optional<Path>;
auto audio_dir() -> Optional<Path>;
auto desktop_dir() -> Optional<Path>;
auto document_dir() -> Optional<Path>;
auto download_dir() -> Optional<Path>;
auto font_dir() -> Optional<Path>;
auto picture_dir() -> Optional<Path>;
auto public_dir() -> Optional<Path>;
auto template_dir() -> Optional<Path>;
auto video_dir() -> Optional<Path>;

} // namespace dire::user
