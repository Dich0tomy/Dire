#include <catch2/catch_test_macros.hpp>

#include <dire/project.hpp>

#include "test_env.hpp"

TEST_CASE("name() normalizes name for platform", "[project_dirs]")
{
	using dire::Path;

	REQUIRE(static_cast<Path>(dire::name("baz", "bar", "foo")) == "bar\\foo");
	REQUIRE(static_cast<Path>(dire::name("foo", " F o o", "     BaZ  ")) == "F o o\\BaZ");
	REQUIRE(static_cast<Path>(dire::name("domain", "x", "     baz -az ")) == "x\\baz -az");
}

TEST_CASE("name() respects IReallyWantMyOwnPlatformProjectName", "[project_dirs]")
{
	auto cache_dir = dire::cache_dir(dire::IReallyWantMyOwnPlatformProjectName(" -Wo w _"));

	REQUIRE(cache_dir->string().ends_with(" -Wo w _\\cache"));
}

TEST_CASE("Dir functions respect name", "[project_dirs]")
{
	auto name = dire::name("domain", "org", "  a _p - p ");

	REQUIRE(dire::config_dir(name)->string().ends_with("org\\a _p - p\\config"));
	REQUIRE(dire::data_dir(name)->string().ends_with("org\\a _p - p\\data"));
	REQUIRE(dire::cache_dir(name)->string().ends_with("org\\a _p - p\\cache"));
	REQUIRE(dire::data_local_dir(name)->string().ends_with("org\\a _p - p\\data"));
	REQUIRE(dire::config_local_dir(name)->string().ends_with("org\\a _p - p\\config"));
	REQUIRE(dire::preference_dir(name)->string().ends_with("org\\a _p - p\\config"));

	REQUIRE(not dire::runtime_dir(name));
	REQUIRE(not dire::state_dir(name));
}
