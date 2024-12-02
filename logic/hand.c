#include "tiles.h"
#include <stdlib.h>

typedef struct Hand {
    Tiles *hand;
    Tiles **chi;
    int chi_len;
    int chi_cap;
    Tiles **pon;
    int pon_len;
    int pon_cap;
    Tiles **kan;
    int kan_len;
    int kan_cap;
    bool opened;
} Hand;

void hand_remove_tile(Hand *hand, int pos) { tiles_remove(hand->hand, pos); }
Tiles *hand_closed_tiles(const Hand *hand) { return hand->hand; }
void hand_add_tile(Hand *hand, Tile *tile) { tiles_add(hand->hand, tile); }
bool is_opened(const Hand *hand) { return hand->opened; }
bool is_closed(const Hand *hand) { return !hand->opened; }

bool hand_is_complete(const Hand *hand) {
    int nchi = hand->chi_len;
    int npon = hand->pon_len;
    tiles_sort(hand->hand);
    for (int i = 0; i < tiles_size(hand->hand); i++) {
        Tile *t = tiles_get(hand->hand, i);
    }
    return (nchi + npon) == 4;
}

void hand_sort(Hand *hand) { tiles_sort(hand->hand); }

bool hand_is_valid(const Hand *hand) { return true; }

Hand *hand_from_string(const char *s) {
    Hand *hand = calloc(sizeof(*hand), 1);
    hand->hand = tiles_from_string(s);
    return hand;
}

void hand_free(Hand *hand) {
    free(hand->hand);
    free(hand->chi);
    free(hand->pon);
    free(hand->kan);
    free(hand);
}
