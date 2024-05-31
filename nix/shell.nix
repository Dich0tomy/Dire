{
  pkgs,
  nativeDeps,
  buildDeps,
  preCommitCheck,
  ...
}: let
  shellDeps = [
    pkgs.doxygen
    pkgs.cmake
    pkgs.graphviz
  ];

  baseShellAttrs = {
    hardeningDisable = ["all"];

    packages = nativeDeps ++ shellDeps;

    buildInputs = buildDeps;
  };

  gccStdenv = pkgs.gcc11Stdenv;

  clangStdenv = pkgs.llvmPackages_16.stdenv;

  ciGcc = pkgs.mkShell.override {stdenv = gccStdenv;} baseShellAttrs;

  ciClang = pkgs.mkShell.override {stdenv = clangStdenv;} baseShellAttrs;

  devPackages =
    [
      pkgs.act
    ]
    ++ shellDeps;

  baseDevShellAttrs =
    baseShellAttrs
    // {
      inherit (preCommitCheck) shellHook;

      packages = baseShellAttrs.packages ++ devPackages;
    };

  devClang = pkgs.mkShell.override {stdenv = clangStdenv;} (baseDevShellAttrs
    // {
      env = {
        CLANGD_PATH = "${pkgs.clang-tools_16}/bin/clangd";
        ASAN_SYMBOLIZER_PATH = "${pkgs.llvmPackages_16.bintools-unwrapped}/bin/llvm-symbolizer";
      };
    });

  devGcc = pkgs.mkShell.override {stdenv = gccStdenv;} baseDevShellAttrs;
in {
  inherit ciGcc ciClang devGcc devClang;
}
