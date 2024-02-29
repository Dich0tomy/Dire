#include <sstream>
#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include <dire/detail/getenv.hpp>
#include <dire/detail/system_dirs/xdg_user_dirs.hpp>

#include "test_env.hpp"

TEST_CASE("Xdg user dirs test", "[xdg_user_dirs]")
{
	tenv::set("HOME", "/home/user/");

	tenv::set("XDG_DATA_HOME", "/home/xdg/.local/share");
	tenv::set("XDG_CONFIG_HOME", "/home/xdg/.config/");
	tenv::set("XDG_STATE_HOME", "/home/xdg/.local/state");
	tenv::set("XDG_CACHE_HOME", "/home/xdg/.cache");
	tenv::set("XDG_RUNTIME_DIR", "/run/xdg/2137");
	// Note that this is not officially supported by the xdg spec
	tenv::set("XDG_BIN_HOME", "/home/xdg/.local/bin");

	SECTION("Reads dirs properly")
	{
		static auto const home = dire::detail::getenv("HOME").value();

		auto stream = std::stringstream(R"DIRS(
																	XDG_DOCUMENTS_DIR =  "$HOME/Documents"
																	XDG_DESKTOP_DIR  =  "$HOME/Desktop"

																	XDG_DOWNLOAD_DIR  =  "/home/bob/Downloads"
																	)DIRS");

		auto xdg_dirs = dire::detail::xdg::all_from_stream(stream, home);

		REQUIRE(xdg_dirs["DOCUMENTS"] == "/home/user/Documents");
		REQUIRE(xdg_dirs["DESKTOP"] == "/home/user/Desktop");

		REQUIRE(xdg_dirs["DOWNLOAD"] == "/home/bob/Downloads");

		REQUIRE(xdg_dirs.size() == 3);
	}

	SECTION("Omits comments")
	{
		static auto const home = dire::detail::getenv("HOME").value();

		auto stream = std::stringstream(R"DIRS(
																	# This is a comment
																	XDG_DESKTOP_DIR="$HOME/Desktop"
																	# Also a comment lol
																	)DIRS");

		auto xdg_dirs = dire::detail::xdg::all_from_stream(stream, home);

		REQUIRE(xdg_dirs.size() == 1);

		REQUIRE(xdg_dirs["DESKTOP"] == "/home/user/Desktop");
	}

	SECTION("Unescapes properly")
	{
		static auto const home = dire::detail::getenv("HOME").value();

		auto stream = std::stringstream(R"DIRS(
																	XDG_DESKTOP_DIR="$HOME/De\\s\$ktop"
																	)DIRS");

		auto xdg_dirs = dire::detail::xdg::all_from_stream(stream, home);

		REQUIRE(xdg_dirs.size() == 1);

		REQUIRE(xdg_dirs["DESKTOP"] == "/home/user/De\\s$ktop");
	}

	SECTION("Omits empty")
	{
		static auto const home = dire::detail::getenv("HOME").value();

		auto stream = std::stringstream(R"DIRS(
																	XDG_DESKTOP_DIR=""
																	XDG_DOWNLOAD_DIR   =       ""
																	)DIRS");

		auto xdg_dirs = dire::detail::xdg::all_from_stream(stream, home);

		REQUIRE(xdg_dirs.empty());
	}

	SECTION("Omits non-xdg")
	{
		static auto const home = dire::detail::getenv("HOME").value();

		auto stream = std::stringstream(R"DIRS(
																	PLENTY_OF="$HOME/Downloads"
																	# Keys here right?
																	XDG_NOT_HERE_LOl="$HOME/"
																	)DIRS");

		auto xdg_dirs = dire::detail::xdg::all_from_stream(stream, home);

		REQUIRE(xdg_dirs.empty());
	}

	SECTION("Omits just $HOME")
	{
		static auto const home = dire::detail::getenv("HOME").value();

		auto stream = std::stringstream(R"DIRS(
																	XDG_DESKTOP_DIR = "$HOME/"
																	XDG_DOCUMENTS_DIR = "$HOME"
																	)DIRS");

		auto xdg_dirs = dire::detail::xdg::all_from_stream(stream, home);

		REQUIRE(xdg_dirs.empty());
	}

	SECTION("Omits invalid pairs")
	{
		static auto const home = dire::detail::getenv("HOME").value();

		auto stream = std::stringstream(R"DIRS(
																	XDG_DESKTOP_DIR
																	A = "
																	= ""
																	)DIRS");

		auto xdg_dirs = dire::detail::xdg::all_from_stream(stream, home);

		REQUIRE(xdg_dirs.empty());
	}
}
