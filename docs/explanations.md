# Explanations

This document tries to explain differences between the directories and which one you should use for certain things.

Some of that information is present in [the reference](https://dich0tomy.github.io/Dire/) as well.

## Local vs non-local dirs

First thing to note is that the difference only exists on window (but you should still opt in for the proper semantic behaviour even if you want to target *nix or macOS).

On windows all base and project dirs begin in `C:\Users\Foo\AppData`. Local ones in `\Local` and non-local ones in `\Roaming`.

The difference is important - on windows the files in roaming can be synchronized across the domain.
This implies you should only store files specific to current machine configuration in the local directories and anything that *can* be synchronized should go into the non-local ones.

As for using the non local version, here's a short version of do's and dont's ([here's a full version](https://learn.microsoft.com/en-us/windows/apps/design/app-settings/store-and-retrieve-app-data#roaming-data-dos-and-donts)):
- Use it only for small files and settings (e.g. config preferences)
- Save references to data instead of whole data (e.g. link to some online article instead of the whole article itself)
- Use it for saving state of work that might be continued (e.g. email drafts)
- Don't save machine specific files

**NOTE**!  
Technically since Windows 11 [roaming data and settings is not deprecated](https://learn.microsoft.com/en-us/windows/whats-new/deprecated-features)
and developers [should integrate with Azure App Service instead](https://learn.microsoft.com/en-us/windows/apps/design/app-settings/store-and-retrieve-app-data#roaming-data) to properly support cross platform syncing.

Relevant references:
- [Windows KNOWNFOLDERID](https://learn.microsoft.com/en-us/windows/win32/shell/knownfolderid?redirectedfrom=MSDN)
- [Store and retrieve settings and other app data](https://learn.microsoft.com/en-us/windows/apps/design/app-settings/store-and-retrieve-app-data)
- [Store and retrieve settings and other app data (roaming section)](https://learn.microsoft.com/en-us/windows/apps/design/app-settings/store-and-retrieve-app-data#roaming-data)
- [Windows Deprecated Features](https://learn.microsoft.com/en-us/windows/whats-new/deprecated-features)

## Config vs preference dir

The difference exists only on macOS (but you should still opt in for the proper semantic behaviour even if you don't target it).

Even though macOS exposes proper directories for different application files, mostly located in `$HOME/Library/...`,
a lot of applications (mainly power user/developer ones) write to directories one would expect to find on linux (like `.config` instead of `/Library/Application Support`).

For this reason, similar to [`directories-rs`](https://github.com/dirs-dev/directories-rs) and as per [Apple's Standard Directories Guide](https://developer.apple.com/library/archive/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/FileSystemOverview/FileSystemOverview.html#//apple_ref/doc/uid/TP40010672-CH2-SW1)
two different directories are exposed - `config` and `preference`:
- The former writes to `.config` and should generally be used for dev tools and such
- The latter writes to `$HOME/Library/Application Support` and should be used for higher levels apps for your "typical joe", who wouldn't necessarily be snooping around files to try and find the config

Relevant references:
- [Apple's Standard Directories Guide](https://developer.apple.com/library/archive/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/FileSystemOverview/FileSystemOverview.html#//apple_ref/doc/uid/TP40010672-CH2-SW1)
- [pdm-project/pdm #1451](https://github.com/pdm-project/pdm/issues/1451)
- [dirs-dev/directories-rs #62](https://github.com/dirs-dev/directories-rs/issues/62)

## Cache, state, data, config

The difference is simple:
- **cache** - for any files which are safe to delete between application restarts, temporary, used as a result of some computation stored for a while, etc.
- **state** - files that are non-portable state of the application - logs, history and such
- **data** - files portable across machines such as icons, fonts, desktop entries and other data files
- **config** - for persistent user configuration files

Relevant references:
- [XDG Base Directory Specificaton](https://specifications.freedesktop.org/basedir-spec/0.8/)
