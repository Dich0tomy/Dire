{
  pkgs,
  version,
}:
pkgs.stdenv.mkDerivation {
  pname = "expected";
  inherit version;

  src = pkgs.fetchFromGitHub {
    owner = "TartanLlama";
    repo = "expected";
    rev = "v${version}";
    sha256 = "sha256-AuRU8VI5l7Th9fJ5jIc/6mPm0Vqbbt6rY8QCCNDOU50=";
  };

  nativeBuildInputs = [pkgs.cmake];

  strictDeps = true;

  postInstall = ''
    install -Dm644 ${./expected.pc} $out/lib/pkgconfig/expected.pc
  '';
}
