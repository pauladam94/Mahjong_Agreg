#ifndef PATTERN_H
#define PATTERN_H
#include "../utils/better_int.h"
#include "../utils/vec.h"
#include "tile.h"
// A Pattern is a given way to think about a Hand. It forces which tiles are use
// to construct the pairs, sequences and three of a kind that are choosen to
// then have complete a Hand
typedef struct Pattern Pattern;
typedef enum GroupType GroupType;

Pattern *pattern_empty();
// Complete deeply a Pattern
Pattern *pattern_copy(const Pattern *pat);
Pattern *pattern_from_tiles(vec(Tile *) tiles);
// Gets the pointers to `tile` in `tiles`at the position `pos` (no copy)
Tile *pattern_get_tile(Pattern *pat, u64 pos);
void pattern_add_group(Pattern *pat, Tile *t1, Tile *t2, Tile *t3);
void pattern_add_pair(Pattern *pat, Tile *t0, Tile *t1);
// Remove the first tiles in the pattern `tiles` that equals `t`
void pattern_remove_tile(Pattern *pat, Tile *t);
void pattern_pp(FILE *file, const Pattern *pat);
// Checks wheter the Pattern contains three group and a pair (no NULL ptr)
void pattern_free(Pattern *pat);
void pattern_next_pair(const Pattern *pat, Tile **fst, Tile **snd);
void pattern_next_sequence(const Pattern *pat, Tile **fst, Tile **snd,
                           Tile **thrd);
void pattern_next_three_same(const Pattern *pat, Tile **fst, Tile **snd,
                             Tile **thrd);
bool pattern_is_complete(const Pattern *pat);
bool pattern_has_pair(Pattern *pat);
bool pattern_has_four_group(Pattern *pat);

vec(vec(Tile *)) pattern_without_pair(Pattern *pat);
vec(vec(Tile *))pattern_get_group(Pattern *pat);
vec(GroupType) pattern_get_group_type(Pattern *pat);
vec(GroupType) pattern_get_group_type_without_pair(Pattern *pat);

bool pattern_is_open(Pattern *pat);

#endif // PATTERN_H
