#include "stdlib.h"
#include "tile.h"

typedef struct {
    int len;
    int cap;
    Tile *arr;
} Hand;

Hand *empty_hand() {
    Hand *hand = calloc(sizeof(*hand), 1);
    return hand;
}
