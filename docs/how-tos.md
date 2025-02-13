# How to's

This document shows a few common operations one would like to perform with this library.

## Basic usage using the function API
```cpp
fmt::println("{}", dire::base::cache_dir().value_or("Couldn't determine cache dir."));
// Will assert if we couldn't determine home dir (wchis is rare, though)
fmt::println("{}", *dire::base::home_dir());

fmt::println("{}", *dire::user::audio_dir());
fmt::println("{}", *dire::user::download_dir());
// This is guaranteed to fail on windows
fmt::println("{}", *dire::user::font_dir());
```

## Basic usage using the bundle API
```cpp
if(auto bundle = dire::base::bundle()) {
	fmt::println("{}", bundle->home_dir);
	fmt::println("{}", bundle->cache_dir);
}

if(auto bundle = dire::user::bundle()) {
	fmt::println("{}", bundle->audio_dir);
	fmt::println("{}", bundle->download_dir);
	// Some fields in the bundle are still optional. This is guaranteed to fail on windows.
	fmt::println("{}", *bundle->font_dir);
}
```

## Using the project API
```cpp
static constexpr auto project_domain = "Me";
static constexpr auto project_org = "Dich0tomy";
static constexpr auto project_app_name = "Dire";

// First we create a "name".
// This is a cross platform path fragment which will get properly appended to various base dirs.
//
// | Platform |       Result      |
// |:--------:|:-----------------:|
// | Linux    | dire              |
// | Mac      | me.dich0tomy.dire |
// | Windows  | Dichotomy/Dire    |
// See the documentation of `dire::project::name()` for more details.
auto const project_name = dire::project::name(project_domain, project_org, project_app_name);

// Then we can use it to obtain a bundle or use the standalone functions:
if(auto bundle = dire::project::bundle(project_name)) {
	fmt::println("{}", bundle->cache_dir);
	fmt::println("{}", bundle->config_dir);
	// Will result with the same as above
	fmt::println("{}", dire::project::cache_dir(project_name));
	fmt::println("{}", dire::project::config_dir(project_name));
}
```

## Using your own name instead of the cross-platform generated one
```cpp
// If you really want to bypass the cross platform name mechanism you can do it that way:
auto name = dire::project::IReallyWantMyOwnPlatformProjectName("whatever you wish, princess");

// `PlatformProjectName` is implicitly constructible from `IReallyWantMyOwnPlatformProjectName`
// so the below just works.
if(auto bundle = dire::project::bundle(name)) {
	fmt::println("{}", bundle->cache_dir);
	fmt::println("{}", bundle->config_dir);
	// Will result with the same as above
	fmt::println("{}", dire::project::cache_dir(name));
	fmt::println("{}", dire::project::config_dir(name));
}
```
