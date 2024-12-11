#include "../model/pattern.h"
#include "../model/tile.h"
#include "../model/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Pattern 3]\n");
    vec(Tile *) tiles = tiles_from_string("1111123123123m234p");
    Pattern *pat = pattern_from_tiles(tiles);

    Tile *fst = NULL;
    Tile *snd = NULL;
    pattern_next_pair(pat, &fst, &snd);
    pattern_free(pat);
}
