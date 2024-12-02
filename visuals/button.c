#include "raylib.h"

bool button_is_pressed(int posX, int posY, int width, int height) {
    int x = GetMouseX();
    int y = GetMouseY();
    float thickness = 7.;
    float roudness = 0.12;
    Rectangle rec = {0};
    rec.x = posX + thickness;
    rec.y = posY + thickness;
    rec.width = width - thickness * 2;
    rec.height = height - thickness * 2;

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
