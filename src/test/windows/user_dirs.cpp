#include <catch2/catch_test_macros.hpp>

#include <dire/user.hpp>

TEST_CASE("Bundle and individual functions return the same", "[user_dirs]")
{
	namespace u = dire::user;
	auto bundle = u::bundle();

	REQUIRE(bundle);

	REQUIRE(*u::home_dir() == bundle->home_dir);
	REQUIRE(*u::audio_dir() == bundle->audio_dir);
	REQUIRE(*u::desktop_dir() == bundle->desktop_dir);
	REQUIRE(*u::document_dir() == bundle->document_dir);
	REQUIRE(*u::download_dir() == bundle->download_dir);
	REQUIRE(*u::picture_dir() == bundle->picture_dir);
	REQUIRE(*u::public_dir() == bundle->public_dir);
	REQUIRE(*u::template_dir() == bundle->template_dir);
	REQUIRE(*u::video_dir() == bundle->video_dir);

	REQUIRE(not u::font_dir());
}
