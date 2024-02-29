#include <catch2/catch_test_macros.hpp>

#include <dire/base.hpp>

#include "test_env.hpp"

TEST_CASE("XDG variables are respected", "[base_dirs]")
{
	namespace b = dire::base;

	tenv::set("HOME", "/home/user");

	tenv::set("XDG_DATA_HOME", "/home/xdg/.local/share");
	tenv::set("XDG_CONFIG_HOME", "/home/xdg/.config");
	tenv::set("XDG_STATE_HOME", "/home/xdg/.local/state");
	tenv::set("XDG_CACHE_HOME", "/home/xdg/.cache");
	tenv::set("XDG_RUNTIME_DIR", "/run/xdg/2137");
	tenv::set("XDG_BIN_HOME", "/home/xdg/.local/bin");

	REQUIRE(*b::home_dir() == "/home/user");

	REQUIRE(*b::config_dir() == "/home/xdg/.config");
	REQUIRE(*b::data_dir() == "/home/xdg/.local/share");
	REQUIRE(*b::state_dir() == "/home/xdg/.local/state");
	REQUIRE(*b::runtime_dir() == "/run/xdg/2137");
	REQUIRE(*b::cache_dir() == "/home/xdg/.cache");
	REQUIRE(*b::executable_dir() == "/home/xdg/.local/bin");
	REQUIRE(*b::data_local_dir() == "/home/xdg/.local/share");
	REQUIRE(*b::config_local_dir() == "/home/xdg/.config");
	REQUIRE(*b::preference_dir() == "/home/xdg/.config");
}

TEST_CASE("Fallbacks properly if XDG vars are not present", "[base_dirs]")
{
	namespace b = dire::base;

	tenv::hide("XDG_DATA_HOME");
	tenv::hide("XDG_CONFIG_HOME");
	tenv::hide("XDG_STATE_HOME");
	tenv::hide("XDG_CACHE_HOME");
	tenv::hide("XDG_RUNTIME_DIR");
	tenv::hide("XDG_BIN_HOME");

	REQUIRE(*b::home_dir() == "/home/user");

	REQUIRE(*b::config_dir() == "/home/user/.config");
	REQUIRE(*b::data_dir() == "/home/user/.local/share");
	REQUIRE(*b::state_dir() == "/home/user/.local/state");
	REQUIRE(*b::cache_dir() == "/home/user/.cache");
	REQUIRE(*b::executable_dir() == "/home/user/.local/bin");
	REQUIRE(*b::data_local_dir() == "/home/user/.local/share");
	REQUIRE(*b::config_local_dir() == "/home/user/.config");
	REQUIRE(*b::preference_dir() == "/home/user/.config");

	REQUIRE(not b::runtime_dir());
}

TEST_CASE("Bundle and individual functions return the same", "[base_dirs]")
{
	namespace b = dire::base;

	// Just to guarantee we at least have a home an runtime dir
	tenv::set("HOME", "/home/user");
	tenv::set("XDG_RUNTIME_DIR", "/run/xdg/2137");

	auto bundle = b::bundle();

	REQUIRE(bundle);

	REQUIRE(*b::home_dir() == bundle->home_dir);

	REQUIRE(*b::config_dir() == bundle->config_dir);
	REQUIRE(*b::data_dir() == bundle->data_dir);
	REQUIRE(*b::state_dir() == bundle->state_dir);
	REQUIRE(*b::runtime_dir() == bundle->runtime_dir);
	REQUIRE(*b::cache_dir() == bundle->cache_dir);
	REQUIRE(*b::executable_dir() == bundle->executable_dir);
	REQUIRE(*b::data_local_dir() == bundle->data_local_dir);
	REQUIRE(*b::config_local_dir() == bundle->config_local_dir);
	REQUIRE(*b::preference_dir() == bundle->preference_dir);
}
