#include "draw.h"
#include "raylib.h"
#include "settings.h"

void DrawBox(Rectangle rec, int thickness, Color color, Align align) {
    float roundness = 0.12;
    DrawRectangleRoundedLinesEx(rec, roundness, 2, thickness, ORANGE);
}

bool button_is_pressed(int posX, int posY, int width, int height, Align align) {
    int x = GetMouseX();
    int y = GetMouseY();
    float thickness = (float)TILE_HEIGHT / 20;
    Rectangle rec = {0};
    switch (align) {
    case DOWN:
        rec.x = posX;
        rec.y = posY;
        rec.width = width;
        rec.height = height;
        break;
    case RIGHT:
        rec.x = posX;
        rec.y = posY - TILE_WIDTH;
        rec.width = height;
        rec.height = width;
        break;
    case UP:
        rec.x = posX - TILE_WIDTH;
        rec.y = posY - TILE_HEIGHT;
        rec.width = width;
        rec.height = height;
        break;
    case LEFT:
        rec.x = posX - TILE_HEIGHT;
        rec.y = posY;
        rec.width = height;
        rec.height = width;
        break;
    }
    rec.x += thickness;
    rec.y += thickness;
    rec.width += - thickness * 2;
    rec.height += - thickness * 2;
    if (rec.x <= x && x <= rec.x + rec.width && rec.y <= y && y <= rec.y + rec.height) {
        if (IsMouseButtonDown(0)) {
            DrawBox(rec, thickness, GREEN, align);
            return true;
        } else {
            DrawBox(rec, thickness, ORANGE, align);
            return false;
        }
    } else {
        return false;
    }
}

bool button_text_is_pressed(int posX, int posY, int width, int height,
                            const char *text, Align align) {
    DrawText(text, posX + 10, posY + 10, 20, BLACK);
    return button_is_pressed(posX, posY, width, height, align);
}
