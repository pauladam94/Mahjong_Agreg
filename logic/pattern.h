#ifndef PATTERN_H
#define PATTERN_H
#include "tile.h"
#include "tiles.h"
// A Pattern is a given way to think about a Hand. It forces which tiles are use
// to construct the pairs, sequences and three of a kind that are choosen to
// then have complete a Hand
typedef struct Pattern Pattern;

Pattern *pattern_empty();
// Complete deeply a Pattern
Pattern *pattern_copy(Pattern *pat);
Pattern *pattern_from_tiles(Tiles *tiles);
Tile *pattern_get_tile(Pattern *pat, int pos);
void pattern_add_group(Pattern *pat, Tile *t1, Tile *t2, Tile *t3);
void pattern_add_pair(Pattern *pat, Tile *t0, Tile *t1);
// Remove the first tiles in the pattern `tiles` that equals `t`
void pattern_remove_tile(Pattern *pat, Tile *t);
void pattern_pp(FILE *file, Pattern *pat);
// Checks wheter the Pattern contains three group and a pair (no NULL ptr)
void pattern_free(Pattern *pat);
void pattern_next_sequence(Pattern *pat, Tile **fst, Tile **snd, Tile **thrd);
void pattern_next_three_same(Pattern *pat, Tile **fst, Tile **snd, Tile **thrd);
bool pattern_is_complete(Pattern *pat);

#endif // PATTERN_H
