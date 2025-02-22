{
  mkShell,
  nil,
  justbuild,
  gcc11Stdenv,
  llvmPackages_16,
  act,
  clang-tools_16,
  doxygen,
  cmake,
  graphviz,
  meson,
  ninja,
  pkg-config,
  catch2_3,
  fmt,
  tl-optional,
  tl-expected,
}: let
  #
  # Packages
  #
  devPackages = [
    act
  ];

  baseShellAttrs = {
    hardeningDisable = ["all"];

    nativeBuildInputs = [
      justbuild
      nil

      meson
      ninja
      pkg-config

      doxygen
      cmake
      graphviz
    ];

    buildInputs = [
      catch2_3
      fmt
      tl-optional
      tl-expected
    ];
  };

  baseDevShellAttrs =
    baseShellAttrs
    // {
      inherit (baseShellAttrs) buildInputs;

      nativeBuildInputs = baseShellAttrs.nativeBuildInputs ++ devPackages;
    };

  #
  # mkShells
  #
  mkGccShell = mkShell.override {stdenv = gcc11Stdenv;};
  mkClangShell = mkShell.override {stdenv = llvmPackages_16.stdenv;};

  #
  # Shells
  #
  ciGcc = mkGccShell baseShellAttrs;
  ciClang = mkClangShell baseShellAttrs;

  devClang = mkClangShell (baseDevShellAttrs
    // {
      env = {
        CLANGD_PATH = "${clang-tools_16}/bin/clangd";
        ASAN_SYMBOLIZER_PATH = "${llvmPackages_16.bintools-unwrapped}/bin/llvm-symbolizer";
      };
    });

  devGcc = mkGccShell baseDevShellAttrs;
in {
  inherit ciGcc ciClang devGcc devClang;
}
