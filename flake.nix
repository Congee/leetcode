{
  description = "cracking the coding interview";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
        let
          pkgs = import nixpkgs { inherit system; };
          llvm = pkgs.llvmPackages_latest;
          lib = nixpkgs.lib;

        in
          {
            devShell = pkgs.mkShell {
              nativeBuildInputs = [
                # builder
                # p.gnumake
                # p.bear
                pkgs.cmake
                # debugger
                llvm.lldb

                # XXX: the order of include matters
                pkgs.clang-tools
                llvm.clang # clangd

                pkgs.gtest
              ];

              buildInputs = [
                # stdlib for cpp
                llvm.libcxx
              ];

              # CXXFLAGS = "-std=c++17";
              CPATH = builtins.concatStringsSep ":" [
                (lib.makeSearchPathOutput "dev" "include" [ llvm.libcxx ])
                (lib.makeSearchPath "resource-root/include" [ llvm.clang ])
              ];
            };
          }
    );
}
