#include "player.h"
#include "../model/align.h"
#include "../view/settings.h"

void player_next(Player *p) { *p = (*p + 1) % 4; }

Vector2 player_pos(Player i) {
    Vector2 pos;
    switch (i) {
    case Player0:
        pos.x = WIDTH / 2 - 7 * TILE_WIDTH;
        pos.y = HEIGHT - TILE_HEIGHT;
        break;
    case Player1:
        pos.x = WIDTH - TILE_HEIGHT;
        pos.y = HEIGHT / 2 + 7 * TILE_WIDTH;
        break;
    case Player2:
        pos.x = WIDTH / 2 - 7 * TILE_WIDTH;
        pos.y = TILE_HEIGHT;
        break;
    case Player3:
        pos.x = TILE_HEIGHT;
        pos.y = HEIGHT / 2 - 7 * TILE_WIDTH;
        break;
    }
    return pos;
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
