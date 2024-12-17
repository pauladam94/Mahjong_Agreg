#include "align.h"
#include "../view/settings.h"
#include "raylib.h"

float align_rotation(Align align) {
    switch (align) {
    case DOWN:
        return 0.;
    case RIGHT:
        return -90.;
    case UP:
        return 180.;
    case LEFT:
        return 90.;
    }
}

Vector2 align_pos_hand(Align align, int posX, int posY, int i,
                       Settings settings) {
    Vector2 res;
    switch (align) {
    case DOWN:
        res.x = posX + i * settings.tile_width;
        res.y = posY;
        break;
    case RIGHT:
        res.x = posX;
        res.y = posY - i * settings.tile_width;
        break;
    case UP:
        res.x = posX + i * settings.tile_width;
        res.y = posY;
        break;
    case LEFT:
        res.x = posX;
        res.y = posY + i * settings.tile_width;
        break;
    }
    return res;
}

Vector2 align_pos_discard(Align align, int posX, int posY, int i,
                          Settings settings) {
    Vector2 pos;
    switch (align) {
    case DOWN:
        pos.x = posX + (i % 6) * settings.tile_width + 3 * settings.tile_width;
        pos.y =
            posY + (i / 6) * settings.tile_height - 4 * settings.tile_height;
        break;
    case RIGHT:
        pos.x =
            posX + (i / 6) * settings.tile_height - 4 * settings.tile_height;
        pos.y = posY - (i % 6) * settings.tile_width - 3 * settings.tile_width;
        break;
    case UP:
        pos.x = posX - (i % 6) * settings.tile_width + 9 * settings.tile_width;
        pos.y =
            posY - (i / 6) * settings.tile_height + 4 * settings.tile_height;
        break;
    case LEFT:
        pos.x =
            posX - (i / 6) * settings.tile_height + 4 * settings.tile_height;
        pos.y = posY + (i % 6) * settings.tile_width + 3 * settings.tile_width;
        break;
    }
    return pos;
}

Rectangle align_rect(Align align, Vector2 pos, Settings settings) {
    Rectangle rec;
    switch (align) {
    case DOWN:
        rec.x = pos.x;
        rec.y = pos.y;
        rec.width = settings.tile_width;
        rec.height = settings.tile_height;
        break;
    case RIGHT:
        rec.x = pos.x;
        rec.y = pos.y - settings.tile_width;
        rec.width = settings.tile_height;
        rec.height = settings.tile_width;
        break;
    case UP:
        rec.x = pos.x - settings.tile_width;
        rec.y = pos.y - settings.tile_height;
        rec.width = settings.tile_width;
        rec.height = settings.tile_height;
        break;
    case LEFT:
        rec.x = pos.x - settings.tile_height;
        rec.y = pos.y;
        rec.width = settings.tile_height;
        rec.height = settings.tile_width;
        break;
    }
    return rec;
}
