#include "player.h"
#include "../view/align.h"
#include "../view/settings.h"

void next_player(Player *p) { *p = (*p + 1) % 4; }

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

Align player_align(const Player i) {
    switch (i) {
    case Player0:
        return DOWN;
    case Player1:
        return RIGHT;
    case Player2:
        return UP;
    case Player3:
        return LEFT;
    }
}
