#include "../model/pattern.h"
#include "../model/patterns.h"
#include "../model/tile.h"
#include "../model/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Patterns 1]\n");
    reset();

    vec(Pattern *) patterns = NULL;
    vec(Tile *) tiles = tiles_from_string("1111123123123m234p");
    Pattern *pat = pattern_from_tiles(tiles);

    patterns = patterns_first_group_pattern(pat);
    patterns_pp(stdout, patterns);
    printf("\n");

    patterns_free(&patterns);
}
