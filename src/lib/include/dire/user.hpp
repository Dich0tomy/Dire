#pragma once

#include <dire/defines.hpp>

namespace dire::user
{

/**
 * A bundle of all user directories.
 * `template_dir` doesn't exist on linux systems
 * `font_dir` doesn't exists on windows.
 *
 * To see example values see the reference for specific standalone functions.
 */
struct UserDirsBundle
{
	Path home_dir;

	Path audio_dir;
	Path desktop_dir;
	Path document_dir;
	Path download_dir;
	Path picture_dir;
	Path video_dir;
	Path public_dir;

	Optional<Path> font_dir;
	Optional<Path> template_dir;
};

/**
 	* Returns a bundle of user directories.
 	*
 	* Fails when home cannot be determined.
 	*
 	* \see UserDirsBundle
*/
auto bundle() -> Optional<UserDirsBundle>;

/**
 	* The home directory. It typically contains all user files and user subfolders.
 	* A lot of programs also write their configuration files in here, either at top level or in `.config`.
 	*
	* | Platform |                    Method                    |    Example   |
	* |:--------:|:--------------------------------------------:|:------------:|
	* | Linux    | $HOME or getpwuid_r if $HOME isn't available | /home/foo    |
	* | Mac      | $HOME or getpwuid_r if $HOME isn't available | /Users/Foo   |
	* | Windows  | Known Folder API FOLDERID_Profile            | C:\Users\Foo |
*/
auto home_dir() -> Optional<Path>;

/**
 	* Typically used to store audio files, programs which download and/or work with audio files may also use it.
	*
	* | Platform |              Method              |       Example      |
	* |:--------:|:--------------------------------:|:------------------:|
	* | Linux    | $XDG_MUSIC_DIR                   | /home/foo/Music    |
	* | Mac      | home_dir() + "/Music"            | /Users/Foo/Music   |
	* | Windows  | Known Folder API FOLDERID_Music  | C:\Users\Foo\Music |
*/
auto audio_dir() -> Optional<Path>;

/**
	* This is the directory whose contents are displayed on the desktop
	* (on Linux desktops are not always available, which is typically the case for Tiling Window Managers).
	*
	* | Platform |               Method              |        Example       |
	* |:--------:|:---------------------------------:|:--------------------:|
	* | Linux    | $XDG_DESKTOP_DIR                  | /home/foo/Desktop    |
	* | Mac      | home_dir() + "/Desktop"           | /Users/Foo/Desktop   |
	* | Windows  | Known Folder API FOLDERID_Desktop | C:\Users\Foo\Desktop |
*/
auto desktop_dir() -> Optional<Path>;

/**
	* Used mostly for plaintext and text processor documents.
	* Lots of other programs may use it as well, especially ones made for designing.
	*
	* | Platform |                Method               |         Example        |
	* |:--------:|:-----------------------------------:|:----------------------:|
	* | Linux    | $XDG_DOCUMENTS_DIR                  | /home/foo/Documents    |
	* | Mac      | home_dir() + "/Documents"           | /Users/Foo/Documents   |
	* | Windows  | Known Folder API FOLDERID_Documents | C:\Users\Foo\Documents |
*/
auto document_dir() -> Optional<Path>;

/**
	* Mostly used by browsers for saved files. Some other programs may utilize it as well.
	*
	* | Platform |                Method               |         Example        |
	* |:--------:|:-----------------------------------:|:----------------------:|
	* | Linux    | $XDG_DOWNLOAD_DIR                   | /home/foo/Downloads    |
	* | Mac      | home_dir() + "/Downloads"           | /Users/Foo/Downloads   |
	* | Windows  | Known Folder API FOLDERID_Downloads | C:\Users\Foo\Downloads |
*/
auto download_dir() -> Optional<Path>;

/**
	* Typically used by programs for downloading and manipulating images.
	*
	* | Platform |               Method               |         Example        |
	* |:--------:|:----------------------------------:|:----------------------:|
	* | Linux    | $XDG_PICTURES_DIR                  | /home/foo/Pictures    |
	* | Mac      | home_dir() + "/Pictures"           | /Users/Foo/Pictures   |
	* | Windows  | Known Folder API FOLDERID_Pictures | C:\Users\Foo\Pictures |
*/
auto picture_dir() -> Optional<Path>;

/**
	* Typically used by programs for downloading videos.
	*
	* Mac has a special case here and names the dir `Movies`
	*
	* | Platform |               Method             |        Example      |
	* |:--------:|:--------------------------------:|:-------------------:|
	* | Linux    | $XDG_VIDEOS_DIR                  | /home/foo/Videos    |
	* | Mac      | home_dir() + "/Pictures"         | /Users/Foo/Movies   |
	* | Windows  | Known Folder API FOLDERID_Videos | C:\Users\Foo\Videos |
*/
auto video_dir() -> Optional<Path>;

/**
	* A directory that all users have access to.
	* This is especially useful for windows and mac which have native solutions for
	* sharing these over network.
	*
	* | Platform |               Method             |        Example      |
	* |:--------:|:--------------------------------:|:-------------------:|
	* | Linux    | $XDG_PUBLICSHARE_DIR             | /home/foo/Public    |
	* | Mac      | home_dir() + "/Public"           | /Users/Foo/Public   |
	* | Windows  | Known Folder API FOLDERID_Public | C:\Users\Foo\Public |
*/
auto public_dir() -> Optional<Path>;

/**
	* Directory for font files.
	*
	* It doesn't exist on windows, as it doesn't have a one, standard directory for fonts.
	* They are typically put and found in `%WINDIR%\Fonts` - typically `C:\Windows\Fonts`
	* or `%LOCALAPPDATA%\Microsoft\Windows\Fonts\` - typically `C:\Users\Foo\AppData\Local\Microsoft\Windows\Fonts`.
	*
	* | Platform |                        Method                     |          Example         |
	* |:--------:|:-------------------------------------------------:|:------------------------:|
	* | Linux    | $XDG_DATA_HOME/fonts or $HOME/.local/share/fonts  | /home/foo/Public         |
	* | Mac      | home_dir() + "/Library/Fonts"                     | /Users/Foo/Library/Fonts |
	* | Windows  | nullopt                                           | nullopt                  |
*/
auto font_dir() -> Optional<Path>;

/**
	* Directory for user template files.
	*
	* On linux users can drop all kinds of template files there, which the desktop environment
	* then picks up and allows creating new documents based on them from a contextual menu.
	*
	* On windows this folder is typically dependent on user programs, like the software from the
	* Microsoft suite or its other alternatives - which means there's a bigger chance for it to fail!
	*
	* | Platform |                 Method              |          Example                                           |
	* |:--------:|:-----------------------------------:|:----------------------------------------------------------:|
	* | Linux    | $XDG_TEMPLATES_DIR                  | /home/foo/Templates                                        |
	* | Mac      | nullopt                             | nullopt                                                    |
	* | Windows  | Known Folder API FOLDERID_Templates | C:\Users\Alice\AppData\Roaming\Microsoft\Windows\Templates |
*/
auto template_dir() -> Optional<Path>;

} // namespace dire::user
