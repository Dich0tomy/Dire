#include <catch2/catch_test_macros.hpp>

#include <dire/user.hpp>

#include "test_env.hpp"

TEST_CASE("Bundle and individual functions return the same", "[user_dirs]")
{
	// Just to guarantee we at least have a home an runtime dir
	tenv::set("HOME", "/home/user");
	tenv::set("XDG_RUNTIME_DIR", "/run/xdg/2137");

	auto bundle = dire::UserDirsBundle::make();

	REQUIRE(bundle);

	REQUIRE(*dire::font_dir() == bundle->font_dir);
	REQUIRE(*dire::audio_dir() == bundle->audio_dir);
	REQUIRE(*dire::desktop_dir() == bundle->desktop_dir);
	REQUIRE(*dire::document_dir() == bundle->document_dir);
	REQUIRE(*dire::download_dir() == bundle->download_dir);
	REQUIRE(*dire::picture_dir() == bundle->picture_dir);
	REQUIRE(*dire::public_dir() == bundle->public_dir);
	REQUIRE(*dire::template_dir() == bundle->template_dir);
	REQUIRE(*dire::video_dir() == bundle->video_dir);
}
