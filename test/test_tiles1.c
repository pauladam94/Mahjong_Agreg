#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Tiles 1]\n");
    reset();
    Tiles *tiles = tiles_empty();
    tiles_add(tiles, tile_from_string("1m"));
    tiles_pp(stdout, tiles);
    printf("\n");
    tiles_free(tiles);
}
