#include "stdlib.h"
#include "tile.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct Hand {
    int len;
    int cap;
    Tile **arr;
    bool opened;
} Hand;

Hand *empty_hand() {
    Hand *hand = calloc(sizeof(*hand), 1);
    return hand;
}

void hand_add_tile(Hand *hand, Tile *tile) {
    hand->len++;
    if (hand->len > hand->cap) {
        hand->cap = (hand->cap == 0) ? 1 : hand->cap * 2;
        hand->arr = realloc(hand->arr, sizeof(hand->arr) * hand->cap);
    }
    hand->arr[hand->len - 1] = tile;
}

Tile *get_tile(const Hand *hand, int pos) { return hand->arr[pos]; }

void hand_remove_tile(Hand *hand, int pos) {
    printf("\nIn Hand Remove Tile\n");
    printf("hand->len :%d\n", hand->len);
    printf("hand->cap :%d\n", hand->cap);
    printf("pos :%d\n", pos);
    if (hand->len == 0) {
        fprintf(stderr, "Removing Tile in Empty Hand\n");
        exit(1);
    }
    memmove(hand->arr + pos, hand->arr + pos + 1,
            sizeof(hand->arr) * (hand->len - pos - 1));
    hand->len--;
}

int hand_size(const Hand *hand) { return hand->len; }

Hand *hand_from_string(const char *s) {
    Hand *hand = empty_hand();
    char tile_string[3] = {0};
    tile_string[2] = '\0';
    int len = 0;
    int cap = 0;
    char *buf = NULL;

    for (int i = 0; i < (int)strlen(s); i++) {
        char c = s[i];
        // if we treat a digit
        if (isdigit(c)) {
            len++;
            if (len > cap) {
                cap = cap == 0 ? 1 : cap * 2;
                buf = realloc(buf, cap);
            }
            buf[len - 1] = c;
        } else {
            for (int j = 0; j < len; j++) {
                tile_string[0] = buf[j];
                tile_string[1] = c;
                Tile *tile = tile_from_string(tile_string);
                hand_add_tile(hand, tile);
            }
            free(buf);
            buf = NULL;
            len = 0;
            cap = 0;
        }
    }
    return hand;
}

void hand_free(Hand *hand) {
    free(hand->arr);
    free(hand);
}

bool is_opened(const Hand *hand) { return hand->opened; }
bool is_closed(const Hand *hand) { return !hand->opened; }
