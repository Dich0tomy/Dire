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
        inputs',
        system,
        lib,
        self',
        ...
      }: let
        pre-commit-check = pre-commit-hooks.lib.${system}.run {
          src = ./.;

          tools = pkgs // {clang-tools = pkgs.clang-tools_16;};

          hooks = {
            editorconfig-checker.enable = true;
            tagref.enable = true;

            clang-format.enable = true;
            clang-tidy.enable = true;
          };
        };

        buildDeps =
          [
            pkgs.ctre
            pkgs.catch2_3
            pkgs.fmt
          ]
          ++ pkgs.callPackage ./nix/dependencies.nix {inherit pkgs;};

        nativeDeps = [
          pkgs.doxygen
          pkgs.graphviz

          pkgs.meson
          pkgs.cmake
          pkgs.ninja
          pkgs.pkg-config
        ];

        rootDir = ./.;

				version = (builtins.readFile ./VERSION);

        package = import ./nix/package/package.nix {inherit pkgs buildDeps nativeDeps rootDir lib version;};
      in {
        formatter = pkgs.alejandra;

        packages.default = package.direRelease;

        devShells = import ./nix/shell.nix {
          inherit pkgs buildDeps nativeDeps pre-commit-check;
        };
      };
    };
}
