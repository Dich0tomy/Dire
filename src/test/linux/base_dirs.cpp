#include <catch2/catch_test_macros.hpp>

#include <dire/base.hpp>

#include "test_env.hpp"

TEST_CASE("XDG variables are respected", "[base_dirs]")
{
	tenv::set("HOME", "/home/user");

	tenv::set("XDG_DATA_HOME", "/home/xdg/.local/share");
	tenv::set("XDG_CONFIG_HOME", "/home/xdg/.config");
	tenv::set("XDG_STATE_HOME", "/home/xdg/.local/state");
	tenv::set("XDG_CACHE_HOME", "/home/xdg/.cache");
	tenv::set("XDG_RUNTIME_DIR", "/run/xdg/2137");
	tenv::set("XDG_BIN_HOME", "/home/xdg/.local/bin");

	REQUIRE(*dire::home_dir() == "/home/user");

	REQUIRE(*dire::config_dir() == "/home/xdg/.config");
	REQUIRE(*dire::data_dir() == "/home/xdg/.local/share");
	REQUIRE(*dire::state_dir() == "/home/xdg/.local/state");
	REQUIRE(*dire::runtime_dir() == "/run/xdg/2137");
	REQUIRE(*dire::cache_dir() == "/home/xdg/.cache");
	REQUIRE(*dire::executable_dir() == "/home/xdg/.local/bin");
	REQUIRE(*dire::data_local_dir() == "/home/xdg/.local/share");
	REQUIRE(*dire::config_local_dir() == "/home/xdg/.config");
	REQUIRE(*dire::preference_dir() == "/home/xdg/.config");
}

TEST_CASE("Fallbacks properly if XDG vars are not present", "[base_dirs]")
{
	tenv::hide("XDG_DATA_HOME");
	tenv::hide("XDG_CONFIG_HOME");
	tenv::hide("XDG_STATE_HOME");
	tenv::hide("XDG_CACHE_HOME");
	tenv::hide("XDG_RUNTIME_DIR");
	tenv::hide("XDG_BIN_HOME");

	REQUIRE(*dire::home_dir() == "/home/user");

	REQUIRE(*dire::config_dir() == "/home/user/.config");
	REQUIRE(*dire::data_dir() == "/home/user/.local/share");
	REQUIRE(*dire::state_dir() == "/home/user/.local/state");
	REQUIRE(*dire::cache_dir() == "/home/user/.cache");
	REQUIRE(*dire::executable_dir() == "/home/user/.local/bin");
	REQUIRE(*dire::data_local_dir() == "/home/user/.local/share");
	REQUIRE(*dire::config_local_dir() == "/home/user/.config");
	REQUIRE(*dire::preference_dir() == "/home/user/.config");

	REQUIRE(not dire::runtime_dir());
}

TEST_CASE("Bundle and individual functions return the same", "[base_dirs]")
{
	// Just to guarantee we at least have a home an runtime dir
	tenv::set("HOME", "/home/user");
	tenv::set("XDG_RUNTIME_DIR", "/run/xdg/2137");

	auto bundle = dire::BaseDirsBundle::make();

	REQUIRE(bundle);

	REQUIRE(*dire::home_dir() == bundle->home_dir);

	REQUIRE(*dire::config_dir() == bundle->config_dir);
	REQUIRE(*dire::data_dir() == bundle->data_dir);
	REQUIRE(*dire::state_dir() == bundle->state_dir);
	REQUIRE(*dire::runtime_dir() == bundle->runtime_dir);
	REQUIRE(*dire::cache_dir() == bundle->cache_dir);
	REQUIRE(*dire::executable_dir() == bundle->executable_dir);
	REQUIRE(*dire::data_local_dir() == bundle->data_local_dir);
	REQUIRE(*dire::config_local_dir() == bundle->config_local_dir);
	REQUIRE(*dire::preference_dir() == bundle->preference_dir);
}
