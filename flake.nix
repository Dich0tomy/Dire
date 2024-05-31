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

      imports = [
        ./nix/dependencies
        ./nix/package
      ];

      perSystem = {
        pkgs,
        system,
        lib,
        ...
      }: {
        formatter = pkgs.alejandra;

        imports = [./nix/shell];
      };
    };
}
