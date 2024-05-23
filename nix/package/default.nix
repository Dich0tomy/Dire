{
  pkgs,
  rootDir,
  version,
  ...
}: let
  package = pkgs.callPackage ./package.nix {
    inherit rootDir version;
  };
in {
  packages.dev = package.dev;
  packages.default = package.out;
}
