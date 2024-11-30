#include "stdlib.h"
#include "tile.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int len;
    int cap;
    Tile **arr;
    bool opened;
} Hand;

Hand *empty_hand() {
    Hand *hand = calloc(sizeof(*hand), 1);
    return hand;
}

void add_tile(Hand *hand, Tile *tile) {
    hand->len += 1;
    if (hand->len > hand->cap) {
        hand->cap = (hand->cap == 0) ? 1 : hand->cap * 2;
        hand->arr = realloc(hand->arr, hand->cap);
    }
    hand->arr[hand->len - 1] = tile;
}

Tile *get_tile(Hand *hand, int pos) { return hand->arr[pos]; }

int get_hand_size(const Hand *hand) { return hand->len; }

Hand *hand_from_string(const char *s) {
    Hand *hand = empty_hand();
    char tile_string[2] = {0};
    int len = 0;
    int cap = 0;
    int *buf = NULL;

    for (int i = 0; i < (int)strlen(s); i++) {
        char c = s[i];
        if (isalpha(c)) {
            len++;
            if (len > cap) {
                cap = cap == 0 ? 1 : cap * 2;
                buf = realloc(buf, cap);
            }
            buf[len - 1] = (int)c - '0';
        } else {
            for (int j = 0; j < len; j++) {
            }
            Tile *tile = tile_from_string(tile_string);
            free(buf);
            len = 0;
            cap = 0;
            add_tile(hand, tile);
        }
    }
    return hand;
}

void free_hand(Hand *hand);

bool is_opened(Hand *hand) { return hand->opened; }
bool is_closed(Hand *hand) { return !hand->opened; }
