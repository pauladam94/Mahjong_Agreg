
#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("=====[TEST Pattern 3]=====\n");
    Tiles *tiles = tiles_from_string("1111123123123m234p");
    Pattern *pat = pattern_from_tiles(tiles);

    Tile *fst = NULL;
    Tile *snd = NULL;
    pattern_next_pair(pat, &fst, &snd);
    if (fst != NULL && snd != NULL) {
        tile_pp(stdout, fst);
        tile_pp(stdout, snd);
    }
    pattern_free(pat);
}
