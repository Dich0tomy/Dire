{
  description = "Complete cross-platform solution for data and user directories discovery.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
    flake-parts.url = "github:hercules-ci/flake-parts";
    systems.url = "github:nix-systems/default";

    pre-commit-hooks = {
      url = "github:cachix/pre-commit-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = inputs @ {pre-commit-hooks, ...}:
    inputs.flake-parts.lib.mkFlake {inherit inputs;} {
      systems = import inputs.systems;
      perSystem = {
        pkgs,
        system,
        lib,
        ...
      }: let
        rootDir = ./.;

        version = lib.strings.fileContents ./VERSION;

        preCommitCheck = pre-commit-hooks.lib.${system}.run {
          src = rootDir;

          tools = pkgs // {clang-tools = pkgs.clang-tools_16;};

          hooks = {
            editorconfig-checker.enable = true;
            tagref.enable = true;

            clang-format.enable = true;
            clang-tidy.enable = true;
          };
        };
      in {
        formatter = pkgs.alejandra;

        _module.args = {
          inherit rootDir version preCommitCheck;

          pkgs = import inputs.nixpkgs {
            inherit system;
            overlays = [
              (f: p: {
                inherit (pkgs.callPackage ./nix/dependencies {}) tl-optional tl-expected;
              })
            ];
          };
        };

        imports = [
          ./nix/package
          ./nix/shell
        ];
      };
    };
}
