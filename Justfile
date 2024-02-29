# Technically this should be make, should it tho?
debug_build_dir := "build_debug"

default:
	@just --list

configure-linux:
	meson configure --buildtype debug --debug -Db_lundef=false -Db_sanitize=address,undefined --warnlevel 3 {{ debug_build_dir }}

configure-windows:
	meson configure --buildtype debug --debug -Db_sanitize=address,undefined --warnlevel 3 {{ debug_build_dir }}

alias sd := setup-debug
setup-debug: && configure-linux
	meson setup {{ debug_build_dir }}

setup-debug-windows: && configure-windows
	meson setup {{ debug_build_dir }}

alias cd := compile-debug
compile-debug:
	meson compile -C {{ debug_build_dir }} dire:static_library

alias ct := compile-tests
compile-tests: setup-debug && compile-debug
	meson compile -C {{ debug_build_dir }} dire_test

alias t := run-tests
[no-exit-message]
run-tests:
	./{{ debug_build_dir }}/src/test/dire_test

# vim: ft=make
