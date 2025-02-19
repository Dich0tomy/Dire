# Dire

> [!NOTE]
> This started as a simple port of [`dirs-dev/directories-rs`](https://github.com/dirs-dev/directories-rs),
> but deviated in the process, the exact details [can be found here](./docs/differences.md).

A complete cross-platform solution for user and data directories discovery with OOTB project support.

|                                         |  **`Dire`** | [`dirs-dev/directories-rs`](https://github.com/dirs-dev/directories-rs) | [`sago007/PlatformFolders`](https://github.com/sago007/PlatformFolders)  |
|:---------------------------------------:|:-----------:|:-----------------------------------------------------------------------:|:------------------------------------------------------------------------:|
| C++                                     |      ✅     |                                 ❌ (Rust)                               |                                    ✅                                    |
| Support for Windows, Linux and Darwin   |      ✅     |                                    ✅                                   |                                    ✅                                    |
| Support for Base, User and Project dirs |      ✅     |                                    ✅                                   |                                    ❌                                    |
| Structure bundles API                   |      ✅     |                                    ❌                                   |                                    ✅                                    |
| Standalone functions API                |      ✅     |                                    ❌                                   |                                    ❌                                    |

An abstract example:
```cpp
static constexpr auto project_domain = "me";
static constexpr auto project_org = "dich0tomy";
static constexpr auto project_app_name = "dire";

auto const project_name = dire::project::name(project_domain, project_org, project_app_name);

auto home_dir = dire::base::home_dir();
if(not home_dir) {
	// Note that `dire::project::bundle` would also fail if this failed
	log::critical("Couldn't determine home directory!");
	return -1;
}

if(auto project_dirs = dire::project::bundle(project_name)) {
	auto config = Config::from_dir(projects_dirs->config_dir);

	App::from_conf(*home_dir, config).start();
} else {
	bail("Couldn't determine basic project dirs.");
}
```

[Tests](./src/test) should be simple, readable and comprehensive enough to show all possible usage examples as well.

## Documentation ([diataxis](https://diataxis.fr)\*)

- [How-To's](./docs/how-tos) - guides on how to do common things
- [Reference](https://dich0tomy.github.io/Dire/) - technical reference (namespaces, functions, etc.)
- [Explanations](./docs/explanations) - explanations of some design choices and **proper usage**

\* It's not a complete diataxis because the scope of this project is simply too small to include reasonable
information in all four sections.

## How it started

This project started because I wanted a nice cross-platform way of discovering typical data directories.

The only feasible alternative I found was [`sago007/PlatformFolders`](https://github.com/sago007/PlatformFolders),
but it doesn't necessarily expose the API I'd like to use.

There's an awesome Rust crate [`dirs-dev/directories-rs`](https://github.com/dirs-dev/directories-rs) which very much
would fit my needs, but it's.. Rust, not C++ - so I wrote this.

## Plans

**\*** Only if there will be need to, e.g. someone asks for that or it will be a feasible fix for an issue.

- [ ] Add conan and vcpkg packaging methods **\***

- [ ] Package returned dirs in special objects with the following methods (this is not necessarily trivial as the notion of `writable` or `readable` is really dependent)**\***:
	- [ ] `writable() -> bool` - cross platform checking if the dir is writable into (we mean every notion of writable - delete, update, create new file, etc.)
	- [ ] `readable() -> bool` - cross platform checking if the dir is readble (same here)
	- [ ] `writable_and_readable() -> bool` - `return writable() and readable();`
	- Since the lib will offer readable(), maybe also try to find font paths on windows?
	Possibly??
	- [ ] `is_empty() -> bool` - checks if the directory is empty
	- [ ] `purge() -> bool` (only for project) - removes the directory with the files inside
	- [ ] `clear() -> bool` (only for project) - clears files inside

	All of these would possibly return something else than `bool` for better error handling, especialy
	`purge()` and `clear()`.

- [ ] Something akin to `appendExtra(Data|Config)Directories` from [`sago007/PlatformFolders`](https://github.com/sago007/PlatformFolders) **\***:

- [ ] Split libdire into totally independent modules, eg. 3 separate targets - base, user and project **\***,
	- The user would not pay for the modules they don't want (possible faster builds, smaller binary size, etc., shouldn't be much of an issue tho, the library is extremely small)
	- Would introduce duplication in certain modules but I guess we're fine with that, the lib is tiny

## License

