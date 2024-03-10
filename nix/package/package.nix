{
  pkgs,
  lib,
  nativeDeps,
  buildDeps,
  rootDir,
  version,
}: let
  dire-pkgconfig = pkgs.substituteAll {
    src = ./dire.pc;
    inherit version;
  };
in
  pkgs.stdenv.mkDerivation {
    pname = "dire";
    inherit version;

    outputs = ["out" "dev"];

    strictDeps = true;
    enableParallelBuilding = true;

    dontUseCmakeConfigure = true;

    nativeBuildInputs = nativeDeps;

    buildInputs = buildDeps;

    src = rootDir;

    mesonBuildType = "release";

		# We use mesonFlags, because mesonFlagsArray & the Nix ecosystem
		# don't have the capabilities to properly handle these flags
		# e.g. appending \ to the one-before-last argument making the command fail
		# or simply not supporting the `-DX=Y` option style
		mesonFlags = [
			"--optimization=3"
			"-Db_lto_threads=8"
			"-Db_lto=true"
			"-Dstrip=true"
		];

    buildPhase = ''
      meson compile dire
    '';

    installPhase = ''
      mkdir -p {$dev,$out}/lib $dev/lib/pkgconfig $dev/include

      cp src/lib/libdire.a $out/lib
      cp src/lib/libdire.a $dev/lib

      cp -r $src/src/lib/include/* $dev/include

      substituteAll ${dire-pkgconfig} $dev/lib/pkgconfig/dire.pc
    '';
  }
