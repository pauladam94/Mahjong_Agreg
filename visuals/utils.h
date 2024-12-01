#ifndef UTILS_H
#define UTILS_H
#include "../logic/hand.h"

// returns -1 if nothing is pressed
// return i > 0 if the i th tile in the hand has been pressed
int hand_tile_pressed(const Hand *hand, int posX, int posY, int degrees);
void draw_hand(const Hand *hand, int posX, int posY, int degrees);
void draw_tile(const Tile *tile, int posX, int posY, int degrees);

#endif // UTILS_H
