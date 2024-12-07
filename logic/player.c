#include "player.h"
#include "../visuals/align.h"
#include "../visuals/settings.h"

void player_position(Player i, int *x, int *y) {
    switch (i) {
    case Player0:
        *x = WIDTH / 2 - 7 * TILE_WIDTH;
        *y = HEIGHT - TILE_HEIGHT;
        break;
    case Player1:
        *x = WIDTH - TILE_HEIGHT;
        *y = HEIGHT / 2 + 7 * TILE_WIDTH;
        break;
    case Player2:
        *x = WIDTH / 2 - 7 * TILE_WIDTH;
        *y = TILE_HEIGHT;
        break;
    case Player3:
        *x = TILE_HEIGHT;
        *y = HEIGHT / 2 - 7 * TILE_WIDTH;
        break;
    }
}

void player_align(const Player i, Align *align) {
    switch (i) {
    case Player0:
        *align = DOWN;
        break;
    case Player1:
        *align = RIGHT;
        break;
    case Player2:
        *align = UP;
        break;
    case Player3:
        *align = LEFT;
        break;
    }
}
