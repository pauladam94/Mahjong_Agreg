#include "../model/hand.h"
#include "../model/tile.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 2]\n");
    Hand* h = hand_from_string("111m2345p7s23m123z");
    hand_add_tile(h, tile_from_string("1m"));
    hand_sort(h);
    hand_free(h);
    reset();
}
