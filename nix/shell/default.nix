{
  pkgs,
  config,
  ...
}: let
  shells = pkgs.callPackages ./shells.nix {inherit (config.legacyPackages) tl-optional tl-expected;};
in {
  devShells = {
    inherit (shells) ciGcc ciClang devGcc devClang;
  };
}
