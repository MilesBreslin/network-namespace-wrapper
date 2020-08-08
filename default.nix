{stdenv, namespace, binary}:

stdenv.mkDerivation {
    name = "network-namespace-wrapper";
    src = ./.;

    buildPhase = ''
        gcc -D 'NAMESPACE="${namespace}"' -D 'BINARY="${binary}"' -o "$(basename ${binary})" main.c
    '';

    installPhase = ''
        mkdir -p $out/bin
        install -m 755 "$(basename ${binary})" $out/bin
    '';
}
