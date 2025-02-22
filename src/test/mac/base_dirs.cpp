#include <catch2/catch_test_macros.hpp>

#include <dire/base.hpp>

#include "test_env.hpp"

TEST_CASE("Proper base dirs are returned", "[base_dirs]")
{
	tenv::set("HOME", "/home/user");

	REQUIRE(*dire::home_dir() == "/home/user");

	REQUIRE(*dire::config_dir() == "/home/user/Library/Application Support");
	REQUIRE(*dire::data_dir() == "/home/user/Library/Application Support");
	REQUIRE(*dire::data_local_dir() == "/home/user/Library/Application Support");
	REQUIRE(*dire::config_local_dir() == "/home/user/Library/Application Support");
	REQUIRE(*dire::preference_dir() == "/home/user/Library/Application Support");
	REQUIRE(*dire::cache_dir() == "/home/user/Library/Caches");

	REQUIRE(not dire::executable_dir());
	REQUIRE(not dire::state_dir());
	REQUIRE(not dire::runtime_dir());
}

TEST_CASE("Bundle and individual functions return the same", "[base_dirs]")
{
	auto bundle = dire::BaseDirsBundle::make();

	REQUIRE(*dire::home_dir() == bundle->home_dir);

	REQUIRE(*dire::config_dir() == bundle->config_dir);
	REQUIRE(*dire::data_dir() == bundle->data_dir);
	REQUIRE(*dire::cache_dir() == bundle->cache_dir);
	REQUIRE(*dire::data_local_dir() == bundle->data_local_dir);
	REQUIRE(*dire::config_local_dir() == bundle->config_local_dir);
	REQUIRE(*dire::preference_dir() == bundle->preference_dir);

	REQUIRE(not dire::executable_dir());
	REQUIRE(not dire::runtime_dir());
	REQUIRE(not dire::state_dir());
}
