#include "../../model/pattern.h"
#include "../../model/tile.h"
#include "../../model/tiles.h"
#include "../../utils/error.h"

int main() {
    purple();
    printf("[TEST Pattern 2]\n");
    reset();

    vec(Tile *) tiles = tiles_from_string("222z234p123m");
    Pattern *pat = pattern_from_tiles(tiles);
    vec(Tile *) pair = NULL;
    vec_push(pair, tile_from_string("1z"));
    vec_push(pair, tile_from_string("1z"));
    pattern_add_group(pat, pair, PAIR_CLOSE);
    pattern_pp(stdout, pat);
    printf("\n");

    pattern_free(pat);
}
