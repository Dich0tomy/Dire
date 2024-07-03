{
	pkgs,
	config,
	...
}:
{
	packages.default = pkgs.callPackage ./package.nix config.legacyPackages;
}
