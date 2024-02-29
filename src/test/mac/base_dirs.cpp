#include <catch2/catch_test_macros.hpp>

#include <dire/base.hpp>

#include "test_env.hpp"

TEST_CASE("Proper base dirs are returned", "[base_dirs]")
{
	namespace b = dire::base;

	tenv::set("HOME", "/home/user");

	REQUIRE(*b::home_dir() == "/home/user");

	REQUIRE(*b::config_dir() == "/home/user/Library/Application Support");
	REQUIRE(*b::data_dir() == "/home/user/Library/Application Support");
	REQUIRE(*b::data_local_dir() == "/home/user/Library/Application Support");
	REQUIRE(*b::config_local_dir() == "/home/user/Library/Application Support");
	REQUIRE(*b::preference_dir() == "/home/user/Library/Preferences");

	REQUIRE(*b::cache_dir() == "/home/user/Library/Caches");

	REQUIRE(not b::executable_dir());
	REQUIRE(not b::state_dir());
	REQUIRE(not b::runtime_dir());
}

TEST_CASE("Bundle and individual functions return the same", "[base_dirs]")
{
	namespace b = dire::base;

	auto bundle = b::bundle();

	REQUIRE(*b::home_dir() == bundle->home_dir);

	REQUIRE(*b::config_dir() == bundle->config_dir);
	REQUIRE(*b::data_dir() == bundle->data_dir);
	REQUIRE(*b::cache_dir() == bundle->cache_dir);
	REQUIRE(*b::data_local_dir() == bundle->data_local_dir);
	REQUIRE(*b::config_local_dir() == bundle->config_local_dir);
	REQUIRE(*b::preference_dir() == bundle->preference_dir);

	REQUIRE(not b::executable_dir());
	REQUIRE(not b::runtime_dir());
	REQUIRE(not b::state_dir());
}
