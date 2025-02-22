#include <catch2/catch_test_macros.hpp>

#include <dire/project.hpp>

#include "test_env.hpp"

TEST_CASE("name() normalizes name for platform", "[base_dirs]")
{
	REQUIRE(static_cast<dire::Path>(dire::name("baz", "bar", "foo")) == "baz.bar.foo");
	REQUIRE(static_cast<dire::Path>(dire::name(" F o o", "foo", "     BaZ  ")) == "F-o-o.foo.BaZ");
	REQUIRE(static_cast<dire::Path>(dire::name("domain", "x", "     baz-az ")) == "domain.x.baz-az");
}

TEST_CASE("name() respects IReallyWantMyOwnPlatformProjectName", "[project_dirs]")
{
	tenv::set("HOME", "/home/user/");

	auto cache_dir = dire::cache_dir(dire::IReallyWantMyOwnPlatformProjectName(" -Wo w _"));
	REQUIRE(*cache_dir == "/home/user/Library/Caches/ -Wo w _");
}
