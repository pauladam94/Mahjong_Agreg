#ifndef TILE_H
#define TILE_H
#include <stdbool.h>
#include <stdio.h>

// Tile is the basic element of a game of mahjong
//
// They should be seen as integers that are copied everywhere on every
// operations that gives you access to a Tile*
typedef struct Tile Tile;

Tile *tile_from_string(const char *);
Tile *next_dora(const Tile *tile);
Tile *tile_random();
int tile_number(const Tile *t);
// Man before Pin before Su before Wind before Dragon
// - In order of next Dora
// - West Wind First
// - White Drago First
// This function take into argument pointers to (Tile *)
int tile_comp(const void *a, const void *b);
bool tile_adjacent(const Tile *t0, const Tile *t1);
bool tile_is_terminal(const Tile* t);
bool tile_is_honor(const Tile *t);
bool tile_is_dragon(const Tile *t);
bool tile_is_wind(const Tile *t);
bool tile_is_family(const Tile *t);
bool tile_same_family(const Tile *t0, const Tile *t1);
bool tile_is_man(const Tile *t);
bool tile_is_pin(const Tile *t);
bool tile_is_su(const Tile *t);
bool tile_equals(const Tile *t0, const Tile *t1);
void tile_pp(FILE *file, const Tile *t);

#endif // TILE_H
