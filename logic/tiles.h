#ifndef TILES_H
#define TILES_H
#include "tile.h"
#include <stdbool.h>
typedef struct Tiles Tiles;

Tiles *tiles_empty(void);
// 1m12p124s1z is the tiles with
// Man 1, Pin 1, Pin 2, Su 1, Su 2, Su 4, East Wind
Tiles *tiles_from_string(const char *s);
Tiles *tiles_copy(const Tiles *tiles);
Tile *tiles_get(const Tiles *tiles, int pos);
int tiles_size(const Tiles *tiles);
void tiles_sort(Tiles *tiles);
void tiles_free(Tiles *tiles);
void tiles_add(Tiles *tiles, const Tile *tile);
void tiles_remove(Tiles *tiles, int pos);
void tiles_pp(FILE *file, const Tiles *tiles);

#endif // TILES_H
