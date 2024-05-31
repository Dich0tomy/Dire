{
  pkgs,
  nativeDeps,
  buildDeps,
  pre-commit-check,
  ...
}: let
	basePackages = [
		pkgs.meson
		pkgs.ninja
		pkgs.just 

		pkgs.doxygen
		pkgs.graphviz
	];

  baseShellAttrs = {
    hardeningDisable = ["all"];

    packages = nativeDeps ++ basePackages;

    buildInputs = buildDeps;
  };

  gccStdenv = pkgs.gcc11Stdenv;

  clangStdenv = pkgs.llvmPackages_16.stdenv;

  ciGcc = pkgs.mkShell.override {stdenv = gccStdenv;} baseShellAttrs;

  ciClang = pkgs.mkShell.override {stdenv = clangStdenv;} baseShellAttrs;

  devPackages = [
    pkgs.act
  ] ++ basePackages;

  baseDevShellAttrs =
    baseShellAttrs
    // {
      inherit (pre-commit-check) shellHook;

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
