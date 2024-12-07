#ifndef PLAYER_H
#define PLAYER_H
#include "../view/align.h"

typedef enum Player { Player0, Player1, Player2, Player3 } Player;

void player_position(Player i, int *x, int *y);
void player_align(const Player i, Align *align);

#endif // PLAYER_H
