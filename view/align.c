#include "align.h"
#include "settings.h"

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

void align_pos_hand(Align align, int *x, int *y, int posX, int posY, int i) {
    switch (align) {
    case DOWN:
        *x = posX + i * TILE_WIDTH;
        *y = posY;
        break;
    case RIGHT:
        *x = posX;
        *y = posY - i * TILE_WIDTH;
        break;
    case UP:
        *x = posX + i * TILE_WIDTH;
        *y = posY;
        break;
    case LEFT:
        *x = posX;
        *y = posY + i * TILE_WIDTH;
        break;
    }
}

void align_pos_discard(Align align, int *x, int *y, int posX, int posY, int i) {
    switch (align) {
    case DOWN:
        *x = posX + (i % 6) * TILE_WIDTH + 3 * TILE_WIDTH;
        *y = posY + (i / 6) * TILE_HEIGHT - 4 * TILE_HEIGHT;
        break;
    case RIGHT:
        *x = posX + (i / 6) * TILE_HEIGHT - 4 * TILE_HEIGHT;
        *y = posY - (i % 6) * TILE_WIDTH - 3 * TILE_WIDTH;
        break;
    case UP:
        *x = posX - (i % 6) * TILE_WIDTH + 9 * TILE_WIDTH;
        *y = posY - (i / 6) * TILE_HEIGHT + 4 * TILE_HEIGHT;
        break;
    case LEFT:
        *x = posX - (i / 6) * TILE_HEIGHT + 4 * TILE_HEIGHT;
        *y = posY + (i % 6) * TILE_WIDTH + 3 * TILE_WIDTH;
        break;
    }
}
