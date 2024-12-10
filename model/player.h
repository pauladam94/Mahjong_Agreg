#ifndef PLAYER_H
#define PLAYER_H
#include "../model/align.h"

typedef enum Player { Player0, Player1, Player2, Player3 } Player;

void player_next(Player *p);
Vector2 player_pos(Player i);
Align player_align(const Player i);

#endif // PLAYER_H
