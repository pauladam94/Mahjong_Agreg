#include "raylib.h"

bool button_is_pressed(int posX, int posY, int width, int height) {
    int x = GetMouseX();
    int y = GetMouseY();
    Rectangle rec = {0};
    rec.x = posX;
    rec.y = posY;
    rec.width = width;
    rec.height = height;
    if (posX <= x && x <= posX + width && posY <= y && y <= posY + height ) {
        if (IsMouseButtonDown(0)) {
            DrawRectangleRoundedLinesEx(rec, 0.2, 2, 2., GREEN);
            return true;
        } else {
            DrawRectangleRoundedLinesEx(rec, 0.2, 2, 2., ORANGE);
            return false;
        }
    } else {
        DrawRectangleRoundedLinesEx(rec, 0.2, 2, 2., BLACK);
        return false;
    }
}
