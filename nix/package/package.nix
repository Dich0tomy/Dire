{
  self,
  version,
  stdenv,
  meson,
  ninja,
  pkg-config,
  catch2_3,
  tl-optional,
  tl-expected,
  fmt,
}:
stdenv.mkDerivation {
  pname = "dire";
  inherit version;

  outputs = ["out" "dev"];

  strictDeps = true;
  enableParallelBuilding = true;

  dontUseCmakeConfigure = true;

  nativeBuildInputs = [
    meson
    ninja
    pkg-config
  ];

  buildInputs = [
    catch2_3
    fmt
    tl-optional
    tl-expected
  ];

  src = "${self}";

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

  postInstall = ''
    mkdir -p $dev/lib/pkgconfig $dev/include

    cp -r $src/src/lib/include/* $dev/include

    substitute \
    	${./dire.pc} \
    	$dev/lib/pkgconfig/dire.pc \
    	--subst-var out \
    	--subst-var version
  '';
}
