#include <catch2/catch_test_macros.hpp>

#include <dire/project.hpp>

#include "test_env.hpp"

TEST_CASE("name() normalizes name for platform", "[project_dirs]")
{
	namespace p = dire::project;

	REQUIRE(static_cast<dire::Path>(p::name("baz", "bar", "foo")) == "foo");
	REQUIRE(static_cast<dire::Path>(p::name(" F o o", "foo", "     BaZ  ")) == "baz");
	REQUIRE(static_cast<dire::Path>(p::name("domain", "x", "     baz  -az ")) == "baz-az");
}

TEST_CASE("name() respects IReallyWantMyOwnPlatformProjectName", "[project_dirs]")
{
	namespace p = dire::project;

	tenv::set("XDG_CACHE_HOME", "/home/xdg/.cache");

	auto cache_dir = p::cache_dir(dire::project::IReallyWantMyOwnPlatformProjectName(" -Wo w _"));
	REQUIRE(cache_dir == "/home/xdg/.cache/ -Wo w _");
}

TEST_CASE("Dir functions respect name", "[project_dirs]")
{
	namespace p = dire::project;

	tenv::set("HOME", "/home/user");

	tenv::set("XDG_DATA_HOME", "/home/xdg/.local/share");
	tenv::set("XDG_CONFIG_HOME", "/home/xdg/.config");
	tenv::set("XDG_STATE_HOME", "/home/xdg/.local/state");
	tenv::set("XDG_CACHE_HOME", "/home/xdg/.cache");
	tenv::set("XDG_RUNTIME_DIR", "/run/xdg/2137");
	tenv::set("XDG_BIN_HOME", "/home/xdg/.local/bin");

	auto name = p::name("matter", "doesnt", "  a _p - p ");

	REQUIRE(*p::config_dir(name) == "/home/xdg/.config/a_p-p");
	REQUIRE(*p::data_dir(name) == "/home/xdg/.local/share/a_p-p");
	REQUIRE(*p::state_dir(name) == "/home/xdg/.local/state/a_p-p");
	REQUIRE(*p::runtime_dir(name) == "/run/xdg/2137/a_p-p");
	REQUIRE(*p::cache_dir(name) == "/home/xdg/.cache/a_p-p");
	REQUIRE(*p::data_local_dir(name) == "/home/xdg/.local/share/a_p-p");
	REQUIRE(*p::config_local_dir(name) == "/home/xdg/.config/a_p-p");
	REQUIRE(*p::preference_dir(name) == "/home/xdg/.config/a_p-p");
}
