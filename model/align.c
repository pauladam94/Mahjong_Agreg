#include "align.h"
#include "../view/settings.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

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
    default:
        fprintf(stderr, "Error: align_rotation\n");
        exit(1);
    }
}

Vector2 align_pos_hand(Align align, int posX, int posY, int i) {
    Vector2 res;
    switch (align) {
    case DOWN:
        res.x = posX + i * TILE_WIDTH;
        res.y = posY;
        break;
    case RIGHT:
        res.x = posX;
        res.y = posY - i * TILE_WIDTH;
        break;
    case UP:
        res.x = posX + i * TILE_WIDTH;
        res.y = posY;
        break;
    case LEFT:
        res.x = posX;
        res.y = posY + i * TILE_WIDTH;
        break;
    }
    return res;
}

Vector2 align_pos_discard(Align align, int posX, int posY, int i) {
    Vector2 pos;
    switch (align) {
    case DOWN:
        pos.x = posX + (i % 6) * TILE_WIDTH + 3 * TILE_WIDTH;
        pos.y = posY + (i / 6) * TILE_HEIGHT - 4 * TILE_HEIGHT;
        break;
    case RIGHT:
        pos.x = posX + (i / 6) * TILE_HEIGHT - 4 * TILE_HEIGHT;
        pos.y = posY - (i % 6) * TILE_WIDTH - 3 * TILE_WIDTH;
        break;
    case UP:
        pos.x = posX - (i % 6) * TILE_WIDTH + 9 * TILE_WIDTH;
        pos.y = posY - (i / 6) * TILE_HEIGHT + 4 * TILE_HEIGHT;
        break;
    case LEFT:
        pos.x = posX - (i / 6) * TILE_HEIGHT + 4 * TILE_HEIGHT;
        pos.y = posY + (i % 6) * TILE_WIDTH + 3 * TILE_WIDTH;
        break;
    }
    return pos;
}

Rectangle align_rect(Align align, Vector2 pos) {
    Rectangle rec;
    switch (align) {
    case DOWN:
        rec.x = pos.x;
        rec.y = pos.y;
        rec.width = TILE_WIDTH;
        rec.height = TILE_HEIGHT;
        break;
    case RIGHT:
        rec.x = pos.x;
        rec.y = pos.y - TILE_WIDTH;
        rec.width = TILE_HEIGHT;
        rec.height = TILE_WIDTH;
        break;
    case UP:
        rec.x = pos.x - TILE_WIDTH;
        rec.y = pos.y - TILE_HEIGHT;
        rec.width = TILE_WIDTH;
        rec.height = TILE_HEIGHT;
        break;
    case LEFT:
        rec.x = pos.x - TILE_HEIGHT;
        rec.y = pos.y;
        rec.width = TILE_HEIGHT;
        rec.height = TILE_WIDTH;
        break;
    }
    return rec;
}
