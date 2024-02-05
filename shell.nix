with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "deej";
  nativeBuildInputs = [ pkg-config ];
  buildInputs = [
    gtk3
    webkit2-sharp
  ];
}
