#include "../../model/pattern.h"
#include "../../model/patterns.h"
#include "../../model/tile.h"
#include "../../model/tiles.h"
#include "../../utils/error.h"

int main() {
    purple();
    printf("[TEST Patterns 4]\n");
    reset();

    vec(Pattern *) patterns = NULL;
    vec(Tile *) tiles = tiles_from_string("222z234p123m");
    Pattern *pat = pattern_from_tiles(tiles);

    // patterns_add_first_group_pattern(patterns, pat);
    patterns_pp(stdout, patterns);

    pattern_free(pat);
    patterns_free(&patterns);
}
