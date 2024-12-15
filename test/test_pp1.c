#include "../model/hand.h"
#include "../model/tile.h"
#include "../utils/error.h"
#include "../utils/pp.h"

int main() {
    purple();
    printf("[TEST pp]\n");
    reset();

    Hand *h = hand_from_string("11m");
    fppf(stdout, "hand = %a\n", &hand_pp, h);

    Tile *t0 = tile_from_string("1m");
    Tile *t1 = tile_from_string("1z");
    Tile *t2 = tile_from_string("7s");

    fppf(stdout, "t0= %a, t1 = %a, t2 = %a\n", &tile_pp, t0, &tile_pp, t1,
         &tile_pp, t2);

    hand_free(h);
}
