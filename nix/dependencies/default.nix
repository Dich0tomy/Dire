{
  inputs,
  system,
  ...
}: {
  perSystem = {system, ...}: {
    _module.args = {
      pkgs = import inputs.nixpkgs {
        inherit system;

        overlays = [
          (_: prev: {
            tl-optional = prev.callPackage ./tl-optional {};
            tl-expected = prev.callPackage ./tl-expected {};
          })
        ];
      };
    };
  };
}
