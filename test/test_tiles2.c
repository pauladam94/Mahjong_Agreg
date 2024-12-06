#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Tiles 2]\n");
    Tiles* tiles = tiles_from_string("1m2p7s3z");
    tiles_free(tiles);
    reset();
}
