{
  description = "Complete cross-platform solution for data and user directories discovery.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
    flake-parts.url = "github:hercules-ci/flake-parts";
    systems.url = "github:nix-systems/default";
  };

  outputs = inputs:
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
      in {
        formatter = pkgs.alejandra;

        _module.args = {
          inherit rootDir version;

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
