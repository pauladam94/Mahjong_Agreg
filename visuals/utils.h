#ifndef UTILS_H
#define UTILS_H
#include "../logic/tiles.h"

// returns -1 if nothing is pressed
// return i > 0 if the i th tile in the tiles has been pressed
int tiles_tile_pressed(const Tiles *tiles, int posX, int posY, int degrees);
void draw_tiles(const Tiles *tiles, int posX, int posY, int degrees);
void draw_tile(const Tile *tile, int posX, int posY, int degrees);

#endif // UTILS_H
