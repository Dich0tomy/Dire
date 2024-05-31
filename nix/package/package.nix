{
  pkgs,
  lib,
  nativeDeps,
  buildDeps,
  rootDir,
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

    src = rootDir;

    strictDeps = true;
    enableParallelBuilding = true;

    dontUseCmakeConfigure = true;

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

  direRelease = direBase.overrideAttrs {
    mesonBuildType = "release";

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
}
