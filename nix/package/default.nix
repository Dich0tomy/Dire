{
	pkgs,
	lib,
	nativeDeps,
	buildDeps,
	rootDir,
	version,
	...
}:
let
	package = pkgs.callPackage ./package.nix {
		inherit nativeDeps buildDeps rootDir version;
	};
in
{
	packages.dev = package.dev;
	packages.default = package.out;
}
