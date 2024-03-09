{
  pkgs,
  lib,
  nativeDeps,
  buildDeps,
  rootDir,
<<<<<<< Updated upstream
  version,
}: let
  dire-pkgconfig-dev = pkgs.substituteAll {
    src = ./dire-dev.pc;
    inherit version;
  };
  dire-pkgconfig-lib = pkgs.substituteAll {
    src = ./dire-dev.pc;
    inherit version;
  };

  direBase = pkgs.stdenv.mkDerivation {
    pname = "dire";
    version = "0.1.0";
=======
	version,
}: let
	dire-pkgconfig = pkgs.substituteAll { src = ./dire.pc; inherit version; };
	in pkgs.stdenv.mkDerivation {
	pname = "dire";
	inherit version;
>>>>>>> Stashed changes

	outputs = ["out" "dev"];

	strictDeps = true;
	enableParallelBuilding = true;

	dontUseCmakeConfigure = true;

<<<<<<< Updated upstream
    # out - dire lib without headers
    # dev - dire lib with headers
    outputs = ["out" "dev"];

    nativeBuildInputs = nativeDeps;
    buildInputs = buildDeps;

    preBuild = ''
      mkdir -p $dev/include
      cp -r $src/lib/include/* $dev/include
    '';

    buildPhase = "meson compile dire:static_library";

    installPhase = ''
      mkdir -p {$dev,$out}/lib/pkgconfig

      cp src/lib/libdire.a $dev/lib
      cp src/lib/libdire.a $out/lib

      substituteAll ${dire-pkgconfig-dev} $dev/lib/pkgconfig/dire.pc
      substituteAll ${dire-pkgconfig-lib} $out/lib/pkgconfig/dire.pc
    '';
  };
=======
	nativeBuildInputs = nativeDeps;

	buildInputs = buildDeps;

	src = rootDir;

	mesonBuildType = "release";

	mesonFlagsArray = [(lib.mesonBool "strip" true)];

	buildPhase = ''
		meson compile dire:static_library
	'';

	installPhase = ''
		mkdir -p {$dev,$out}/lib $dev/lib/pkgconfig $dev/include
>>>>>>> Stashed changes

		cp src/lib/libdire.a $out/lib
		cp src/lib/libdire.a $dev/lib

<<<<<<< Updated upstream
    mesonFlagsArray = [(lib.mesonBool "strip" true)];
  };

  direTest = direBase.overrideAttrs {
    hardeningDisable = ["fortify"];

    enableParallelChecking = true;

    mesonBuildType = "debug";

    buildPhase = "meson compile dire_test";

    outputs = ["out"];

    mesonFlags = [
      "--warnlevel=3"
      (lib.mesonOption "b_lundef" "false")
      (lib.mesonOption "cpp_debugstl" "true")
      (lib.mesonOption "b_sanitize" "address,undefined")
    ];

    doCheck = true;

    checkPhase = "src/test/dire_test";

    installPhase = "touch $out";

    meta.mainProgram = "dire_test";
  };
in {
  inherit direRelease;
  inherit direTest;
=======
		cp -r $src/src/lib/include/* $dev/include

		substituteAll ${dire-pkgconfig} $dev/lib/pkgconfig/dire.pc
	'';
>>>>>>> Stashed changes
}
