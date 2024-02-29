#include <catch2/catch_test_macros.hpp>

#include <dire/project.hpp>

#include "test_env.hpp"

TEST_CASE("name() normalizes name for platform", "[project_dirs]")
{
	namespace p = dire::project;
	using dire::Path;

	REQUIRE(static_cast<Path>(p::name("baz", "bar", "foo")) == "baz\\foo");
	REQUIRE(static_cast<Path>(p::name(" F o o", "foo", "     BaZ  ")) == "F o o\\BaZ");
	REQUIRE(static_cast<Path>(p::name("domain", "x", "     baz -az ")) == "domain\\baz -az");
}

TEST_CASE("name() respects IReallyWantMyOwnPlatformProjectName", "[project_dirs]")
{
	namespace p = dire::project;

	auto cache_dir = p::cache_dir(dire::project::IReallyWantMyOwnPlatformProjectName(" -Wo w _"));

	REQUIRE(cache_dir->string().ends_with(" -Wo w _\\cache"));
}

TEST_CASE("Dir functions respect name", "[project_dirs]")
{
	namespace p = dire::project;

	auto name = p::name("domain", "org", "  a _p - p ");

	REQUIRE(p::config_dir(name)->string().ends_with("domain\\a _p - p\\config"));
	REQUIRE(p::data_dir(name)->string().ends_with("domain\\a _p - p\\data"));
	REQUIRE(p::cache_dir(name)->string().ends_with("domain\\a _p - p\\cache"));
	REQUIRE(p::data_local_dir(name)->string().ends_with("domain\\a _p - p\\data"));
	REQUIRE(p::config_local_dir(name)->string().ends_with("domain\\a _p - p\\config"));
	REQUIRE(p::preference_dir(name)->string().ends_with("domain\\a _p - p\\config"));

	REQUIRE(not p::runtime_dir(name));
	REQUIRE(not p::state_dir(name));
}
