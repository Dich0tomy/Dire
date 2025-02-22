#include <catch2/catch_test_macros.hpp>

#include <dire/project.hpp>

#include "test_env.hpp"

TEST_CASE("name() normalizes name for platform", "[project_dirs]")
{
	REQUIRE(static_cast<dire::Path>(dire::name("baz", "bar", "foo")) == "foo");
	REQUIRE(static_cast<dire::Path>(dire::name(" F o o", "foo", "     BaZ  ")) == "baz");
	REQUIRE(static_cast<dire::Path>(dire::name("domain", "x", "     baz  -az ")) == "baz-az");
}

TEST_CASE("name() respects IReallyWantMyOwnPlatformProjectName", "[project_dirs]")
{
	tenv::set("XDG_CACHE_HOME", "/home/xdg/.cache");

	auto cache_dir = dire::cache_dir(dire::IReallyWantMyOwnPlatformProjectName(" -Wo w _"));
	REQUIRE(cache_dir == "/home/xdg/.cache/ -Wo w _");
}

TEST_CASE("Dir functions respect name", "[project_dirs]")
{
	tenv::set("HOME", "/home/user");

	tenv::set("XDG_DATA_HOME", "/home/xdg/.local/share");
	tenv::set("XDG_CONFIG_HOME", "/home/xdg/.config");
	tenv::set("XDG_STATE_HOME", "/home/xdg/.local/state");
	tenv::set("XDG_CACHE_HOME", "/home/xdg/.cache");
	tenv::set("XDG_RUNTIME_DIR", "/run/xdg/2137");
	tenv::set("XDG_BIN_HOME", "/home/xdg/.local/bin");

	auto name = dire::name("matter", "doesnt", "  a _p - p ");

	REQUIRE(*dire::config_dir(name) == "/home/xdg/.config/a_p-p");
	REQUIRE(*dire::data_dir(name) == "/home/xdg/.local/share/a_p-p");
	REQUIRE(*dire::state_dir(name) == "/home/xdg/.local/state/a_p-p");
	REQUIRE(*dire::runtime_dir(name) == "/run/xdg/2137/a_p-p");
	REQUIRE(*dire::cache_dir(name) == "/home/xdg/.cache/a_p-p");
	REQUIRE(*dire::data_local_dir(name) == "/home/xdg/.local/share/a_p-p");
	REQUIRE(*dire::config_local_dir(name) == "/home/xdg/.config/a_p-p");
	REQUIRE(*dire::preference_dir(name) == "/home/xdg/.config/a_p-p");
}
