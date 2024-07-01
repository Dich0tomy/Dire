{
  description = "Complete cross-platform solution for data and user directories discovery.";

  outputs = inputs:
    inputs.flake-parts.lib.mkFlake {inherit inputs;} {
      systems = ["aarch64-darwin" "aarch64-linux" "x86_64-darwin" "x86_64-linux"];


      imports = [
        ./nix/dependencies
        ./nix/package
      ];

      perSystem = {pkgs, ...}: {
        formatter = pkgs.alejandra;

        imports = [./nix/shell];
      };
    };

	inputs = {
		nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
		flake-parts.url = "github:hercules-ci/flake-parts";
	};
}
