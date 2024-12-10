#ifndef TILES_H
#define TILES_H
#include "tile.h"
#include <stdbool.h>
typedef struct Tiles Tiles;

Tiles *tiles_empty(void);
// 1m12p124s1z is the tiles with
// Man 1, Pin 1, Pin 2, Su 1, Su 2, Su 4, East Wind
Tiles *tiles_from_string(const char *s);
// Deep copy of the tiles (conserving the order)
Tiles *tiles_copy(const Tiles *tiles);
Tiles *tiles_all(void);
Tile *tiles_random_from(const Tiles *from);
Tile *tiles_get(const Tiles *tiles, int pos);
int tiles_size(const Tiles *tiles);
void tiles_sort(Tiles *tiles);
void tiles_free(Tiles *tiles);
void tiles_add(Tiles *tiles, Tile *tile);
// Remove tile at a given position in tiles
void tiles_remove(Tiles *tiles, int pos);
// Remove first tile in tiles equals `tile` and return it's position
int tiles_remove_equals(Tiles *tiles, Tile *tile);
// Remove a random tile and return it
Tile *tiles_pick_from(Tiles *from);
void tiles_pp(FILE *file, const Tiles *tiles);

#endif // TILES_H
