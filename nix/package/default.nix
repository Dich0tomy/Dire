{
  pkgs,
  rootDir,
  version,
  ...
}: {
  packages.default = pkgs.callPackage ./package.nix {
    inherit rootDir version;
  };
}
