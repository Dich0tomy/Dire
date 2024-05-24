{
  mkShell,
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
  baseShellDeps = [
    doxygen
    cmake
    graphviz
  ];

  devPackages = [
    act
  ];

  baseShellAttrs = {
    hardeningDisable = ["all"];

    packages =
      [
        meson
        ninja
        pkg-config

        catch2_3
        fmt
        tl-optional
        tl-expected
      ]
      ++ baseShellDeps;
  };

  baseDevShellAttrs =
    baseShellAttrs
    // {
      packages = baseShellAttrs.packages ++ devPackages;
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
