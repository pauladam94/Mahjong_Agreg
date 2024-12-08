#ifndef PLAYER_H
#define PLAYER_H
#include "../view/align.h"

typedef enum Player { Player0, Player1, Player2, Player3 } Player;

void next_player(Player *p);
void player_position(Player i, int *x, int *y);
Align player_align(const Player i);

#endif // PLAYER_H
