{
  pkgs,
  lib,
  nativeDeps,
  buildDeps,
  rootDir,
}: let
  direBase = pkgs.stdenv.mkDerivation {
    pname = "dire";
    version = "0.1.0";

    src = rootDir;

    strictDeps = true;
    enableParallelBuilding = true;

    dontUseCmakeConfigure = true;

    # out - dire app
    # dev - dire lib with headers
    # lib - dire lib without headers
    outputs = ["out" "lib" "dev"];

    nativeBuildInputs = nativeDeps;
    buildInputs = buildDeps;
    preBuild = ''
      mkdir -p $dev/include
      cp -r $src/include/* $dev/include
    '';

    buildPhase = "meson compile dire:static_library dire:executable";

    installPhase = ''
      mkdir -p {$lib,$dev,$out}/lib/pkgconfig $out/bin

      cp src/lib/libdire.a $lib/lib
      cp src/lib/libdire.a $dev/lib
      cp src/lib/libdire.a $out/lib

      substituteAll ${./dire-dev.pc} $dev/lib/pkgconfig/dire.pc
      substituteAll ${./dire-dev.pc} $out/lib/pkgconfig/dire.pc
      substituteAll ${./dire-lib.pc} $lib/lib/pkgconfig/dire.pc

      cp src/app/dire $out/bin
    '';
  };

  direRelease = direBase.overrideAttrs {
    mesonBuildType = "release";

    mesonFlagsArray = [
      (lib.mesonBool "strip" true)
    ];

    meta = {
      mainProgram = "dire";
      outputs = ["out" "lib" "dev"];
    };
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
      # (lib.mesonOption "cpp_debugstl" "true")
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
