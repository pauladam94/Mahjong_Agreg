#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Tile Tile;

Tile *tile_from_string(const char *);
int get_number(Tile t);
bool is_adjacent(Tile t0, Tile t1);
bool is_honor(Tile t);
bool is_dragon(Tile t);
bool is_wind(Tile t);
bool is_family(Tile t);
Image tile_image(const Tile *t);
void pp_tile(FILE *file, Tile *t);

#endif // TILE_H
