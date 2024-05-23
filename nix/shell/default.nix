{
  pkgs,
  preCommitCheck,
  ...
}: let
  shells = pkgs.callPackage ./shells.nix {inherit preCommitCheck;};
in {
  devShells = {
    inherit (shells) ciGcc ciClang devGcc devClang;
  };
}
