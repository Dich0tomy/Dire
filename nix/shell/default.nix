{pkgs, ...}: let
  shells = pkgs.callPackages ./shells.nix {};
in {
  devShells = {
    inherit (shells) ciGcc ciClang devGcc devClang;
  };
}
