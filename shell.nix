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
    openlibm
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

    # X11 dependencies
    xorg.libX11
    xorg.libX11.dev
    xorg.libXcursor
    xorg.libXi
    xorg.libXinerama
    xorg.libXrandr
    raylib
  ];
  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath (with pkgs; [
    wayland
    glfw-wayland
    libxkbcommon
    libGL
    openlibm
  ]);
}
