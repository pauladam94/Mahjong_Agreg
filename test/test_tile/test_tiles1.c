#include "../../model/tile.h"
#include "../../model/tiles.h"
#include "../../utils/error.h"

int main() {
    purple();
    printf("[TEST Tiles 1]\n");
    reset();
    vec(Tile *) tiles = NULL;
    vec_push(tiles, tile_from_string("1m"));
    tiles_pp(stdout, tiles);
    printf("\n");
    vec_free(tiles);
}
