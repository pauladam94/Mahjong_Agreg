#ifndef HAND_H
#define HAND_H
#include "patterns.h"
#include "tiles.h"
#include <stdbool.h>

// A Hand is all tiles that the player is "using" or is assigned to
// - the tiles in this hand.
// - the open tiles in a chi, kan or pon
// - the tiles in his discards
typedef struct Hand Hand;

Hand *hand_empty(void);
Hand *hand_draw_from(Tiles *from, int n);
Hand *hand_from_string(const char *s);
// 4 sequences or three same tile and 1 pair
bool hand_is_complete(const Hand *hand);
// complete with a yaku (or yaku that are enough alone)
bool hand_is_valid(const Hand *hand);
// Hand is complete without any terminal or honor
bool hand_is_all_simple(const Hand *hand);
bool hand_is_opened(const Hand *hand);
bool hand_is_closed(const Hand *hand);
void hand_add_tile(Hand *hand, Tile *tile);
// Remove a tile in the hand and free the tile at the position `pos`
// void hand_remove_tile(Hand *hand, int pos);
// Discard a tile in the hand and put in the discard of the hand.
void hand_discard_tile(Hand *hand, Tile *tile);
void hand_free(Hand *hand);
void hand_sort(Hand *hand);
void hand_pp(FILE *file, const Hand *hand);
Tiles *hand_closed_tiles(const Hand *hand);
Tiles *hand_discarded_tiles(const Hand *hand);

Patterns *hand_patterns(const Hand *hand);

#endif // HAND_H
