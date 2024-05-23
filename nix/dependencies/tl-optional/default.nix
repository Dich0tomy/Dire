{
  pkgs,
  version,
}:
pkgs.stdenv.mkDerivation {
  pname = "optional";
  inherit version;

  src = pkgs.fetchFromGitHub {
    owner = "TartanLlama";
    repo = "optional";
    rev = "v${version}";
    sha256 = "sha256-WPTXTQmzJjAIJI1zM6svZZTO8gP/jt5xDHHRCCu9cmI=";
  };

  strictDeps = true;

  nativeBuildInputs = [pkgs.cmake];

  postInstall = ''
    install -Dm644 ${./optional.pc} $out/lib/pkgconfig/optional.pc
  '';
}
