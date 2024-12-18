#include "raylib.h"

void zoom_gui() {
    if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
        if (IsKeyPressed(KEY_EQUAL)) { // Ctrl + '+' (zoom in)
            SetWindowSize(GetScreenWidth() * 1.1, GetScreenHeight() * 1.1);
        } else if (IsKeyPressed(KEY_MINUS)) { // Ctrl + '-' (zoom out)
            SetWindowSize(GetScreenWidth() * 0.9, GetScreenHeight() * 0.9);
        }
    }
}
