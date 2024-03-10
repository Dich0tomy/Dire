{pkgs}: let
  tl-optional = pkgs.stdenv.mkDerivation rec {
    pname = "optional";
    version = "1.1.0";

    src = pkgs.fetchFromGitHub {
      owner = "TartanLlama";
      repo = "optional";
      rev = "v${version}";
      sha256 = "sha256-WPTXTQmzJjAIJI1zM6svZZTO8gP/jt5xDHHRCCu9cmI=";
    };

    strictDeps = true;

    nativeBuildInputs = [pkgs.cmake];

    postInstall = ''
      mkdir -p $out/lib/pkgconfig
      substituteAll ${./pkg-config/optional.pc} $out/lib/pkgconfig/optional.pc
    '';
  };

  tl-expected = pkgs.stdenv.mkDerivation rec {
    pname = "expected";
    version = "1.1.0";

    src = pkgs.fetchFromGitHub {
      owner = "TartanLlama";
      repo = "expected";
      rev = "v${version}";
      sha256 = "sha256-AuRU8VI5l7Th9fJ5jIc/6mPm0Vqbbt6rY8QCCNDOU50=";
    };

    nativeBuildInputs = [pkgs.cmake];

    strictDeps = true;

    postInstall = ''
      mkdir -p $out/lib/pkgconfig
      substituteAll ${./pkg-config/expected.pc} $out/lib/pkgconfig/expected.pc
    '';
  };
in [
  tl-optional
  tl-expected
]
