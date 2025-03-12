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
          pkgs = import nixpkgs {
            inherit system;
            # XXX: There is no easy way to avoid libstdc++ include files. See
            # https://discourse.nixos.org/t/use-clang-without-gccs-c-standard-library/9884
            # https://discourse.nixos.org/t/how-to-override-stdenv-for-all-packages-in-mkshell/10368/10
            # https://discourse.nixos.org/t/gcc11stdenv-and-clang/17734
            # overlays = [ (_: super: { stdenvNoCC = super.llvmPackages_latest.libcxxStdenv; }) ];
            config.replaceStdenv = { pkgs, ...}: (if pkgs.stdenv.isLinux then pkgs.llvmPackages_latest else pkgs).stdenv;
          };

          llvm = (if pkgs.stdenv.isLinux then pkgs.pkgsLLVM else pkgs).llvmPackages_latest;
          lib = nixpkgs.lib;

        in
          {
            devShell = llvm.stdenv.mkDerivation {
              name = "shell";
              nativeBuildInputs = [
                # builder
                # p.gnumake
                # p.bear
                pkgs.cmake  # for discovering libraries
                pkgs.pkg-config
                pkgs.meson
                pkgs.ninja
                # debugger
                # llvm.lldb
                # pkgs.gdb

                pkgs.gtest
                pkgs.fmt

                pkgs.leetcode-cli

                llvm.bintools
                # Don't use clangd from llvm.clang. It cannot find libcxx's
                # include/c++/v1 despite listing it in search paths
                # clang++ -E -x c++ - -v < /dev/null >/dev/null
                llvm.clang-tools
              ] ++ lib.optionals llvm.stdenv.isLinux [ llvm.lld ]
              ;
              shellHook = lib.optionalString llvm.stdenv.isLinux ''
                export CC_LD="lld"
                export CXX_LD="lld"
              '';
              LD_LIBRARY_PATH = lib.strings.makeLibraryPath [ pkgs.fmt pkgs.gtest llvm.libcxx ];
              LLVM_PROFILE_FILE="/tmp/test.profraw";
            };
          }
    );
}
