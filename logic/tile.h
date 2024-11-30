#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Tile Tile;

Tile *tile_from_string(const char *);
Tile *next_dora(const Tile *tile);
Image tile_image(const Tile *t);
// - if it's a family : number of the tile
// - else : -1 (dragon / winds)
int get_number(Tile *t);
void pp_tile(FILE *file, Tile *t);
void free_tile(Tile *tile);
bool is_adjacent(Tile *t0, Tile *t1);
bool is_honor(Tile *t);
bool is_dragon(Tile *t);
bool tiles_equals(Tile *t1, Tile *t2);
bool is_wind(Tile *t);
bool is_family(Tile *t);

#endif // TILE_H
