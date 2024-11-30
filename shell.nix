{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell {
  packages = with pkgs; [
    wayland
    wayland-protocols
    libxkbcommon
    glfw-wayland
    glfw
    clang
    bear
  ];

  BuildInputs = with pkgs; [
    wayland
    wayland-protocols
    libxkbcommon
    glfw-wayland
    glfw
  ];

  nativeBuildInputs = with pkgs; [
    libGL

    # xorg.libXft
    # libatomic_ops
    # mesa
    # alsa-lib
    # glibc
    # [Wayland]


    # X11 dependencies
    xorg.libX11
    xorg.libX11.dev
    xorg.libXcursor
    xorg.libXi
    xorg.libXinerama
    xorg.libXrandr
    raylib

    # pkgs.glfw-wayland
    # glfw-wayland
    # pkgs.wayland-protocols

    # Web support (uncomment to enable)
    # pkgs.emscripten

  ];
  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath (with pkgs; [
    wayland
    glfw-wayland
    libxkbcommon
    libGL
    # any other libraries that need to be dynamically linked to
  ]);
  # LD_LIBRARY_PATH = "${lib.makeLibraryPath buildInputs}";
}

# devShell = pkgs.mkShell {
#   packages = with pkgs; [
#     rustup
#     cmake
#     clang
#     pkg-config
#     wayland
#     glfw
#   ];
#   LD_LIBRARY_PATH = with pkgs; lib.makeLibraryPath [
#     libGL
#     xorg.libXrandr
#     xorg.libXinerama
#     xorg.libXcursor
#     xorg.libXi
#   ];
#   LIBCLANG_PATH = "${pkgs.llvmPackages_11.libclang.lib}/lib";
# };
