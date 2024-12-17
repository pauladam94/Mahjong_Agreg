#include "player.h"
#include "../model/align.h"
#include "../view/settings.h"

void player_next(Player *p) { *p = (*p + 1) % 4; }

Vector2 player_pos(Player i, Settings settings) {
    Vector2 pos;
    switch (i) {
    case Player0:
        pos.x = (float)settings.width / 2 - 7 * settings.tile_width;
        pos.y = settings.height - settings.tile_height;
        break;
    case Player1:
        pos.x = settings.width - settings.tile_height;
        pos.y = (float)settings.height / 2 + 7 * settings.tile_width;
        break;
    case Player2:
        pos.x = (float)settings.width / 2 - 7 * settings.tile_width;
        pos.y = settings.tile_height;
        break;
    case Player3:
        pos.x = settings.tile_height;
        pos.y = (float)settings.height / 2 - 7 * settings.tile_width;
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
