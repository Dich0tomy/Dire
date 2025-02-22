#pragma once

#include <dire/defines.hpp>

namespace dire
{

/**
 * A bundle of all base directories.
 *
 * These are directories used mostly internally by various programs
 * for storing their caches, configs and other state.
 *
 * `executable_dir`, `runtime_dir` and `state_dir` don't exist on windows and macOS.
 */
struct BaseDirsBundle
{
	static auto make() -> Optional<BaseDirsBundle>;

	/// \copydoc UserDirsBundle::home_dir
	Path home_dir;

	/**
		* A directory for program caches.  
		* Only caches should be stored here (files safe to delete, i.e. download caches), not files that are meant to be persisted.
		*
		* For configuration files:
		* 	`config_dir`, `config_local_dir` or `preference_dir`
		* 	- Files used to alter the behaviour of the application to the user preferences.
		* 	- The user may wish and typically does back up those.
		*
		* For state files:
		* 	`state_dir` (doesn't exist on windows and macOS! Use `bundle.state_dir.value_or(bundle.data_local_dir)`)
		* 	- State of the app - logs, history and such.
		* 	- Typically not portable files unique for the machine the app runs on.
		*
		* For data files:
		* 	`data_dir`, `data_local_dir`
		* 	- Files portable across machines - icons, fonts, desktop entries and such.
		*
		* | Platform |                  Method                  |           Example          |
		* |:--------:|:----------------------------------------:|:--------------------------:|
		* | Linux    | `$XDG_CACHE_HOME` or `$HOME/.cache`      | /home/foo/.cache           |
		* | Mac      | `home_dir()` + "/Library/Caches"         | /Users/Foo/Library/Caches  |
		* | Windows  | Known Folder API `FOLDERID_LocalAppData` | C:\Users\Foo\AppData\Local |
	*/
	Path cache_dir;

	/**
		* A directory for program configuration files.  
		* Only configuration files should be stored here, as users often back up this directory.
		*
		* On linux and macOS this is the same as `config_local_dir`.  
		* On windows this directory can be synchronized in a domain.
		*
		* For applications that are meant for power users, developers, etc., prefer this. Otherwise, prefer `preference_dir`.  
		* This matters on macOS as it stores the configuration files in `$HOME/.config` instead of `$HOME/Library/Preferences`.
		*
		* For cache files:
		* 	`cache_dir`
		* 	- Intermediate files created for more expensive processes.
		* 	- Saved data used to speed up the application by not computing things unnecessarilly.
		* 	- Generally cached files that the user will not care for.
		*
		* For state files:
		* 	`state_dir` (doesn't exist on windows and macOS! Use `bundle.state_dir.value_or(bundle.data_local_dir)`)
		* 	- State of the app - logs, history and such.
		* 	- Typically not portable files unique for the machine the app runs on.
		*
		* For data files:
		* 	`data_dir`, `data_local_dir`
		* 	- Files portable across machines - icons, fonts, desktop entries and such.
		*
		*
		* | Platform |                   Method                   |             Example          |
		* |:--------:|:------------------------------------------:|:----------------------------:|
		* | Linux    | `$XDG_CONFIG_HOME` or `$HOME/.config`      | /home/foo/.config            |
		* | Mac      | `home_dir()` + "/.config"                   | /Users/Foo/.config          |
		* | Windows  | Known Folder API `FOLDERID_RoamingAppData` | C:\Users\Foo\AppData\Roaming |
	*/
	Path config_dir;

	/**
		* A directory for program configuration files for the current user only.  
		* Only configuration files should be stored here, as users often back up this directory.
		*
		* On linux and macOS this is the same as `config_dir`.  
		* On windows this directory cannot be synchronized in the domain as opposed to `config_dir`.
		*
		* For applications that are meant for power users, developers, etc., prefer this. Otherwise, prefer `preference_dir`.  
		* This matters on macOS as it stores the configuration files in `$HOME/.config` instead of `$HOME/Library/Preferences`.
		*
		* For cache files:
		* 	`cache_dir`
		* 	- Intermediate files created for more expensive processes.
		* 	- Saved data used to speed up the application by not computing things unnecessarilly.
		* 	- Generally cached files that the user will not care for.
		*
		* For state files:
		* 	`state_dir` (doesn't exist on windows and macOS! Use `bundle.state_dir.value_or(bundle.data_local_dir)`)
		* 	- State of the app - logs, history and such.
		* 	- Typically not portable files unique for the machine the app runs on.
		*
		* For data files:
		* 	`data_dir`, `data_local_dir`
		* 	- Files portable across machines - icons, fonts, desktop entries and such.
		*
		*
		* | Platform |                  Method                  |           Example          |
		* |:--------:|:----------------------------------------:|:--------------------------:|
		* | Linux    | `$XDG_CONFIG_HOME` or `$HOME/.config`    | /home/foo/.config          |
		* | Mac      | `home_dir()` + "/.config"                | /Users/Foo/.config         |
		* | Windows  | Known Folder API `FOLDERID_LocalAppData` | C:\Users\Foo\AppData\Local |
	*/
	Path config_local_dir;

	/**
		* A directory for program data files.  
		* Used for files inherently portable across machines like icons, fonts, desktop entries and such.
		*
		* On linux and macOS this is the same as `data_local_dir`.  
		* On windows this directory can be synchronized in a domain.
		*
		* For state files:
		* 	`state_dir` (doesn't exist on windows and macOS! Use `bundle.state_dir.value_or(bundle.data_local_dir)`)
		* 	- State of the app - logs, history and such.
		* 	- Typically not portable files unique for the machine the app runs on.
		*
		* For cache files:
		* 	`cache_dir`
		* 	- Intermediate files created for more expensive processes.
		* 	- Saved data used to speed up the application by not computing things unnecessarilly.
		* 	- Generally cached files that the user will not care for.
		*
		* For configuration files:
		* 	`config_dir`, `config_local_dir` or `preference_dir`
		* 	- Files used to alter the behaviour of the application to the user preferences.
		* 	- The user may wish and typically does back up those.
		*
		* | Platform |                     Method                    |                 Example                |
		* |:--------:|:---------------------------------------------:|:--------------------------------------:|
		* | Linux    | `$XDG_DATA_HOME` or `$HOME/.local/share`      | /home/foo/.local/share                 |
		* | Mac      | `home_dir()` + "/Library/Application Support" | /Users/Foo/Library/Application Support |
		* | Windows  | Known Folder API `FOLDERID_RoamingAppData`    | C:\Users\Foo\AppData\Roaming           |
	*/
	Path data_dir;

	/**
		* A directory for program data files for the current user only.  
		* Used for files inherently portable across machines like icons, fonts, desktop entries and such.
		*
		* On linux and macOS this is the same as `data_dir`.  
		* On windows this directory cannot be synchronized in the domain as opposed to `data_dir`.
		*
		* For state files:
		* 	`state_dir` (doesn't exist on windows and macOS! Use `bundle.state_dir.value_or(bundle.data_local_dir)`)
		* 	- State of the app - logs, history and such.
		* 	- Typically not portable files unique for the machine the app runs on.
		*
		* For cache files:
		* 	`cache_dir`
		* 	- Intermediate files created for more expensive processes.
		* 	- Saved data used to speed up the application by not computing things unnecessarilly.
		* 	- Generally cached files that the user will not care for.
		*
		* For configuration files:
		* 	`config_dir`, `config_local_dir` or `preference_dir`
		* 	- Files used to alter the behaviour of the application to the user preferences.
		* 	- The user may wish and typically does back up those.
		*
		* | Platform |                     Method                    |                 Example                |
		* |:--------:|:---------------------------------------------:|:--------------------------------------:|
		* | Linux    | `$XDG_DATA_HOME` or `$HOME/.local/share`      | /home/foo/.local/share                 |
		* | Mac      | `home_dir()` + "/Library/Application Support" | /Users/Foo/Library/Application Support |
		* | Windows  | Known Folder API `FOLDERID_LocalAppData`      | C:\Users\Foo\AppData\Local             |
	*/
	Path data_local_dir;

	/**
		* A directory for program configuration files.  
		* Only configuration files should be stored here, as users often back up this directory.
		*
		* For applications that are meant for ordinary users prefer this.  
		* For applications meant for developers and power users prefer `config_dir` or `config_local_dir`.  
		* This matters on macOS as it stores the configuration files in `$HOME/Library/Preferences` instead of `$HOME/.config`.
		*
		* For cache files:
		* 	`cache_dir`
		* 	- Intermediate files created for more expensive processes.
		* 	- Saved data used to speed up the application by not computing things unnecessarilly.
		* 	- Generally cached files that the user will not care for.
		*
		* For state files:
		* 	`state_dir` (doesn't exist on windows and macOS! Use `bundle.state_dir.value_or(bundle.data_local_dir)`)
		* 	- State of the app - logs, history and such.
		* 	- Typically not portable files unique for the machine the app runs on.
		*
		* For data files:
		* 	`data_dir`, `data_local_dir`
		* 	- Files portable across machines - icons, fonts, desktop entries and such.
		*
		* | Platform |                  Method                  |           Example          |
		* |:--------:|:----------------------------------------:|:--------------------------:|
		* | Linux    | `$XDG_CACHE_HOME` or `$HOME/.cache`      | /home/foo/.cache           |
		* | Mac      | `home_dir()` + "/Library/Caches"         | /Users/Foo/Library/Caches  |
		* | Windows  | Known Folder API `FOLDERID_LocalAppData` | C:\Users\Foo\AppData\Local |
	*/
	Path preference_dir;

	/** A user writable directory for binaries.
		* This is not officialy supported by the XDG specification!
		*
		* This directory doesn't exist on windows and macOS!
		*
		* | Platform |       Method       |        Example       |
		* |:--------:|:------------------:|:--------------------:|
		* | Linux    | `$XDG_BIN_HOME`    | /home/foo/.local/bin |
		* | Mac      | nullopt            | nullopt              |
		* | Windows  | nullopt            | nullopt              |
	*/
	Optional<Path> executable_dir;

	/**  Used for user-specific non-essential runtime files and other file objects (such as sockets, named pipes, ...)
		* - The directory MUST be owned by the user, and the user MUST be the only one having read and write access to it
		* - Its Unix access mode MUST be 0700
		* - It should be used for communication and synchronization purposes
		* - Large files should not be placed in here, since it might reside in runtime memory and cannot necessarily be swapped out to disk
		* - It may be subject to periodic cleanup.
		*
		* This directory doesn't exist on windows and macOS!
		*
		* | Platform |       Method       |    Example    |
		* |:--------:|:------------------:|:-------------:|
		* | Linux    | `$XDG_RUNTIME_DIR` | /run/foo/1000 |
		* | Mac      | nullopt            | nullopt       |
		* | Windows  | nullopt            | nullopt       |
	*/
	Optional<Path> runtime_dir;

	/**
		* A directory for state files - logs, history and such.
		*
		* This directory doesn't exist on windows and macOS! Use `bundle.state_dir.value_or(bundle.data_local_dir)`.
		*
		* For cache files:
		* 	`cache_dir`
		* 	- Intermediate files created for more expensive processes.
		* 	- Saved data used to speed up the application by not computing things unnecessarilly.
		* 	- Generally cached files that the user will not care for.
		*
		* For configuration files:
		* 	`config_dir`, `config_local_dir` or `preference_dir`
		* 	- Files used to alter the behaviour of the application to the user preferences.
		* 	- The user may wish and typically does back up those.
		*
		* For data files:
		* 	`data_dir`, `data_local_dir`
		* 	- Files portable across machines - icons, fonts, desktop entries and such.
		*
		* | Platform |                   Method                   |             Example          |
		* |:--------:|:------------------------------------------:|:----------------------------:|
		* | Linux    | `$XDG_STATE_HOME` or `$HOME/.local/state`  | /home/foo/.local/state       |
		* | Mac      | nullopt                                    | nullopt                      |
		* | Windows  | nullopt                                    | nullopt                      |
	*/
	Optional<Path> state_dir;
};

/// \copydoc BaseDirsBundle::home_dir
auto home_dir() -> Optional<Path>;

/// \copydoc BaseDirsBundle::cache_dir
auto cache_dir() -> Optional<Path>;

/// \copydoc BaseDirsBundle::config_dir
auto config_dir() -> Optional<Path>;

/// \copydoc BaseDirsBundle::config_local_dir
auto config_local_dir() -> Optional<Path>;
/// \copydoc BaseDirsBundle::data_dir
auto data_dir() -> Optional<Path>;

/// \copydoc BaseDirsBundle::data_local_dir
auto data_local_dir() -> Optional<Path>;

/// \copydoc BaseDirsBundle::preference_dir
auto preference_dir() -> Optional<Path>;

/// \copydoc BaseDirsBundle::executable_dir
auto executable_dir() -> Optional<Path>;

/// \copydoc BaseDirsBundle::runtime_dir
auto runtime_dir() -> Optional<Path>;

/// \copydoc BaseDirsBundle::state_dir
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

} // namespace dire
