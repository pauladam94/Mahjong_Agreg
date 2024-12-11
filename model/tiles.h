#ifndef TILES_H
#define TILES_H
#include "../utils/vec.h"
#include "tile.h"
#include <stdbool.h>

// 1m12p124s1z is the tiles with
// Man 1, Pin 1, Pin 2, Su 1, Su 2, Su 4, East Wind
vec(Tile *) tiles_from_string(const char *s);
// Deep copy of the tiles (conserving the order)
vec(Tile *) tiles_copy(const vec(Tile *) tiles);
vec(Tile *) tiles_all(void);
Tile *tiles_random_from(const vec(Tile *) from);

void tiles_sort(vec(Tile *) tiles);

// Remove first tile in tiles equals `tile` and return it's position
int tiles_remove_equals(vec(Tile *) tiles, Tile *tile);
// Remove a random tile and return it
Tile *tiles_pick_from(vec(Tile *) from);
void tiles_pp(FILE *file, const vec(Tile *) tiles);

#endif // TILES_H
