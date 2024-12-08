#ifndef DRAW_H
#define DRAW_H
#include "../model/hand.h"
#include "../model/tiles.h"
#include "align.h"

// returns -1 if nothing is pressed
// return i > 0 if the i th tile in the tiles has been pressed
Tile *hand_tile_pressed(const Hand *hand, int posX, int posY, Align align);
int tiles_tile_pressed(const Tiles *tiles, int posX, int posY, int degrees);
void draw_tiles(const Tiles *tiles, int posX, int posY, Align align);

void tile_draw(const Tile *tile, int posX, int posY, Align align);
void tiles_free_textures();


#endif // DRAW_H
