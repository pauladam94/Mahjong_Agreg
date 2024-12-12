#include "../model/tile.h"
#include "../model/pattern.h"
#include "../model/patterns.h"
#include "../model/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Patterns 1]\n");
    Patterns *patterns = NULL;
    vec(Tile *) tiles = tiles_from_string("1111123123123m234p");
    Pattern *pat = pattern_from_tiles(tiles);

    patterns_add_first_group_pattern(patterns, pat);

    patterns_free(patterns);
}
