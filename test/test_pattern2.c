#include "../model/pattern.h"
#include "../model/tile.h"
#include "../model/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Pattern 2]\n");
    reset();

    vec(Tile *) tiles = tiles_from_string("222z234p123m");
    Pattern *pat = pattern_from_tiles(tiles);
    pattern_add_pair(pat, tile_from_string("1z"), tile_from_string("1z"));
    pattern_pp(stdout, pat);
    printf("\n");

    pattern_free(pat);
}
