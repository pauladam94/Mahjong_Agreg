#ifndef HAND_H
#define HAND_H
#include "../utils/vec.h"
#include "../view/context.h"
#include "player.h"
#include <stdbool.h>
#include "tile.h"
#include "pattern.h"

// A Hand is all tiles that the player is "using" or is assigned to
// - the tiles in this hand.
// - the open tiles in a chi, kan or pon
// - the tiles in his discards
typedef struct Hand Hand;

Hand *hand_empty(Player player);
void hand_pick_from(Hand *hand, vec(Tile *) from);
Hand *hand_from_string(const char *s);
// [4 sequences or three same tile] and [1 pair]
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
void hand_draw(Hand *hand);
vec(Tile *) hand_closed_tiles(const Hand *hand);
vec(Tile *) hand_discarded_tiles(const Hand *hand);
// Update the hand according to the context, returns true if turn has to change
bool hand_update(Hand *hand, vec(Tile *) tiles, Context ctx);
void hand_update_pos_transi(Hand *hand);
vec(Pattern *) hand_patterns(const Hand *hand);

int hand_get_hand_hover(Hand *hand);
int hand_get_discard_hover(Hand *hand);

#endif // HAND_H
