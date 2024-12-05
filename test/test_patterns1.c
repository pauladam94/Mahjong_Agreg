#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Patterns]\n");
    Patterns *patterns = patterns_empty();
    Tiles *tiles = tiles_from_string("1111123123123m234p");
    Pattern *pat = pattern_from_tiles(tiles);

    patterns_add_first_group_pattern(patterns, pat);

    patterns_free(patterns);
    pattern_free(pat);
}
