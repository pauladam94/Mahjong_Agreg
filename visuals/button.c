#include "raylib.h"

bool button_is_pressed(int posX, int posY, int width, int height) {
    int x = GetMouseX();
    int y = GetMouseY();
    Rectangle rec = {0};
    rec.x = posX;
    rec.y = posY;
    rec.width = width;
    rec.height = height;
    float thickness = 4.;
    float roudness = 0.2;
    if (posX <= x && x <= posX + width && posY <= y && y <= posY + height) {
        if (IsMouseButtonDown(0)) {
            DrawRectangleRoundedLinesEx(rec, roudness, 2, thickness, GREEN);
            return true;
        } else {
            DrawRectangleRoundedLinesEx(rec, roudness, 2, thickness, ORANGE);
            return false;
        }
    } else {
        DrawRectangleRoundedLinesEx(rec, roudness, 2, thickness, BLACK);
        return false;
    }
}

bool button_text_is_pressed(int posX, int posY, int width, int height,
                            const char *text) {
    DrawText(text, posX + 10, posY + 10, 20, BLACK);
    return button_is_pressed(posX, posY, width, height);
}
