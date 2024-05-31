{pkgs, ...}: let
  shells = pkgs.callPackage ./shells.nix {};
in {
  devShells = {
    inherit (shells) ciGcc ciClang devGcc devClang;
  };
}
