#include "pattern.h"
#include "patterns.h"
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

void hand_pp(FILE *file, const Hand *hand) { tiles_pp(file, hand->hand); }
Patterns *hand_patterns(const Hand *hand) {
    Patterns *res = patterns_empty();
    Patterns *todo = patterns_empty();
    Tiles *tiles = tiles_copy(hand->hand);

    // Add in the first pattern the different chi and su
    Pattern* pat = pattern_from_tiles(tiles);
    patterns_add_pattern(todo, pat);

    while (patterns_size(todo) != 0) {
        Pattern *pattern = patterns_pop(todo);
        printf("res:");
        patterns_pp(stdout, res);
        printf("\n");
        printf("todo:");
        patterns_pp(stdout, todo);
        printf("\n");

        pattern_pp(stdout, pattern);
        printf("\n");

        if (pattern_is_complete(pattern)) {
            patterns_add_pattern(res, pattern);
            continue;
        }
        patterns_add_first_group_pattern(todo, pattern);
    }
    patterns_free(todo);
    tiles_free(tiles);
    pattern_free(pat);
    return res;
}

bool hand_is_complete(const Hand *hand) {
    Patterns *patterns = hand_patterns(hand);
    patterns_pp(stdout, patterns);
    int n_patterns = patterns_size(patterns);
    patterns_free(patterns);
    return n_patterns >= 1;
}

void hand_sort(Hand *hand) { tiles_sort(hand->hand); }

bool hand_is_valid(const Hand *hand) {
    printf("TODO hand_is_valid\nhand:");
    hand_pp(stdout, hand);
    return true;
}

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
