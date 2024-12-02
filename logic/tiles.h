#ifndef tiles_H
#define tiles_H

#include "tile.h"
#include <stdbool.h>

typedef struct Tiles Tiles;

Tiles *empty_tiles(void);
// 1m12p124s1z is the tiles with Man 1, Pin 1, Pin 2, Su 1, Su 2, Su 4, West
// Wind
Tiles *tiles_from_string(const char *s);

Tile *get_tile(const Tiles *tiles, int pos);

int tiles_size(const Tiles *tiles);
void tiles_free(const Tiles *tiles);
void tiles_add_tile(Tiles *tiles, Tile *tile);
void tiles_remove_tile(Tiles *tiles, int pos);

bool is_yaku(const Tiles *tiles);
bool is_opened(const Tiles *tiles);
bool is_closed(const Tiles *tiles);
#endif // tiles_H
