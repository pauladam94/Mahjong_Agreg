#ifndef TILE_H
#define TILE_H

#include <stdbool.h>
typedef struct Tile Tile;

bool is_adjacent(Tile t0, Tile t1);
bool is_honor(Tile t);
bool is_dragon(Tile t);
bool is_wind(Tile t);
bool is_family(Tile t);

#endif // TILE_H
