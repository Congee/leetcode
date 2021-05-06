{
  description = "leetcode goes brrrrrrrrrrrrrrrrr";

  inputs = {
    nixpkgs.url      = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url  = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
  flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
      # XXX: the order of include matters
      dotclangd = with pkgs; writeText ".clangd" ''
        CompileFlags:
          Add:
            - --include-directory=${lib.makeSearchPathOutput "dev" "include/c++/v1" [ libcxx ]}
            - --include-directory=${lib.makeSearchPathOutput "dev" "include" [ glibc ]}
            - -std=c++17
      '';
    in
    {
      devShell = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          clang_11
          clang-tools
        ];

        # Why does not environment variables like C_INCLUDE_DIR work?
        # FIXME: clean up the side effect
        shellHook = with pkgs; ''
          alias lc=leetcode
          cp --force ${dotclangd} .clangd
        '';
      };
    }
  );
}
