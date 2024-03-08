# Dire

> [!WARNING]
> Still **WIP**. Wait a few days before this gets properly released
> with proper docs and build options.

> [!NOTE]
> This started as a simple port of [`dirs-dev/directories-rs`](https://github.com/dirs-dev/directories-rs),
> but deviated in the process, the exact details [can be found here](./docs/differences.md).

A complete cross-platform solution for user and data directories discovery with OOTB project support. 

TODO:
- [x] Add tests for everything (the tests are probably not perfect but good enough for now)
- [x] Add bundle functions (a function returning a struct with all the paths)
- [x] Refactor so far #1
- [x] Package with Nix \[ "lib" "dev" "bin " ]
- [x] Add proper meson building (with subprojects)
- [x] Add proper CMake building (with FetchContent)
- [x] Add proper license :)))
- [x] Remove CTRE fir xdg parsing
- [x] CI
	- [x] Linux - Nix with { CMake, Meson } x { Gcc, Clang }
	- [x] Mac - Nix with { CMake, Meson } x { Gcc, Clang }
	- [x] Windows - { CMake, Meson } x MSVC
- [x] Merge PR and go public
- [x] Change codeowners
- [x] Documentation generation
- [ ] Add conan and vcpkg packaging methods
- [ ] Add dire executable
- [ ] Write docs with diataxis fr
- [ ] Releases on GitHub
- [ ] Refactor so far #3
- [ ] Better readme (diataxis docs)
- [ ] Refactor so far #4

Plans:
- [ ] Package returned dirs in special objects with the following methods **\***:
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

- [ ] Rewrite the library to be C++17 or even C++11 compatible **\***:
	- That would require throwing out CTRE and rolling our own simple XDG record parser

- [ ] Allow for WebAsm targets **\***:

- [ ] Split the underlying xdg dirs and known folders api into a separate lib **\***:

**\*** Only if there will be need to, e.g. someone asks for that or it will be a feasible fix for an issue
