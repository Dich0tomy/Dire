#pragma once

#include <dire/base.hpp>

#include <dire/defines.hpp>

namespace dire
{

/**
 * Use this class to override `PlatformProjectName` with your own custom name.
 *
 * This is **not** recommended.
 */
class IReallyWantMyOwnPlatformProjectName
{
public:
	explicit IReallyWantMyOwnPlatformProjectName(Path name)
		: name(std::move(name))
	{}

	explicit operator Path const&() const { return name; }

	explicit operator Path() && { return std::move(name); }

private:
	Path name;
};

/**
 * This class stores the platform-specific project name, which is used as a subpath for the project directories.
 *
 * It should be obtained via a call to `dire::name()`, which returns a name standarized for the build platform.
 *
 * If you **REALLY** want to enforce your own name, initialize it by using `IReallyWantMyOwnPlatformProjectName`.
 *
 * This object is passed into `dire::ProjectDirsBundle::make()` or all of project free functions,
 * which return valid project directories.
 */
class PlatformProjectName
{
public:
	PlatformProjectName(IReallyWantMyOwnPlatformProjectName name)
		: name(std::move(name))
	{}

	explicit operator Path const&() const { return name; }

	explicit operator Path() && { return std::move(name); }

private:
	friend auto name(std::string domain, std::string org, std::string app_name) -> PlatformProjectName;

	explicit PlatformProjectName(Path name)
		: name(std::move(name))
	{}

	Path name;
};

/**
 * A bundle of all project directories.
 *
 * These directories can be used to store project specific caches, configs, data, etc.
 *
 * `runtime_dir` and `state_dir` don't exist on windows and macOS.
 */
struct ProjectDirsBundle
{
	static auto make(PlatformProjectName project_name) -> Optional<ProjectDirsBundle>;

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
		* This matters on macOS as it stores the configuration files in `$HOME/.config` instead of `$HOME/Library/Application Support`.
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
		* This matters on macOS as it stores the configuration files in `$HOME/.config` instead of `$HOME/Library/Application Support`.
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
		* This matters on macOS as it stores the configuration files in `$HOME/Library/Application Support` instead of `$HOME/.config`.
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

/**
	* Used to obtain a platform specific `PlatformProjectName` which is used for obtaining
	* project specific directories for caches, configs and such.
	*
	* If you want to override the name to your own one, initialize `PlatformProjectName` directly
	* with `IReallyWantMyOwnPlatformProjectName`.
	*
	* On linux only `app_name` is used and produces a name that is lowercased and with spaces removed.
	* On windows only `app_name` and `org` are used and produces a path like `domain / name` without other modifications.
	* On mac all three are used and produce a name like `domain.org.app_name` with all free segments lowercased and spaces replaced with hyphens.
	* e.g. `dire::name("me", "dich0tomy", "dire")` will produce:
	* | Platform |       Result      |
	* |:--------:|:-----------------:|
	* | Linux    | dire              |
	* | Mac      | me.dich0tomy.dire |
	* | Windows  | Dichotomy/Dire    |
*/
auto name(std::string domain, std::string org, std::string app_name) -> PlatformProjectName;

/// \copydoc ProjectDirsBundle::cache_dir
auto cache_dir(PlatformProjectName project_name) -> Optional<Path>;

/// \copydoc ProjectDirsBundle::config_dir
auto config_dir(PlatformProjectName project_name) -> Optional<Path>;

/// \copydoc ProjectDirsBundle::config_local_dir
auto config_local_dir(PlatformProjectName project_name) -> Optional<Path>;

/// \copydoc ProjectDirsBundle::data_dir
auto data_dir(PlatformProjectName project_name) -> Optional<Path>;

/// \copydoc ProjectDirsBundle::data_local_dir
auto data_local_dir(PlatformProjectName project_name) -> Optional<Path>;

/// \copydoc ProjectDirsBundle::preference_dir
auto preference_dir(PlatformProjectName project_name) -> Optional<Path>;

/// \copydoc ProjectDirsBundle::runtime_dir
auto runtime_dir(PlatformProjectName project_name) -> Optional<Path>;

/// \copydoc ProjectDirsBundle::state_dir
auto state_dir(PlatformProjectName project_name) -> Optional<Path>;

namespace detail
{

auto trim(std::string str) -> std::string;

auto concat_project_path(Path const& path, PlatformProjectName project_name) -> Path;

auto map_project_path(Optional<Path> path, PlatformProjectName project_name) -> Optional<Path>;

} // namespace detail

} // namespace dire
