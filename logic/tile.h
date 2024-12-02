#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Tile Tile;

Tile *tile_from_string(const char *);
Tile *next_dora(const Tile *tile);
Tile* tile_copy(const Tile* tile);
int tile_number(Tile *t);
bool is_adjacent(Tile *t0, Tile *t1);
bool is_honor(Tile *t);
bool is_dragon(Tile *t);
bool is_wind(Tile *t);
bool is_family(Tile *t);
bool is_man(Tile* t);
bool is_pin(Tile* t);
bool is_su(Tile* t);
bool tile_equals(const Tile *t1, const Tile *t2);
Texture2D tile_texture(const Tile *t);
void free_tiles_textures();
void pp_tile(FILE *file, Tile *t);
void free_tile(Tile *tile);

#endif // TILE_H
