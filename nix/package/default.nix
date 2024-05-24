{self, ...}: {
  perSystem = {
    pkgs,
    lib,
    ...
  }: let
    version = lib.strings.fileContents "${self}/VERSION";
  in {
    packages.default = pkgs.callPackage ./package.nix {
      inherit self version;
    };
  };
}
