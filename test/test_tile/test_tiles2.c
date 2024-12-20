#include "../../model/tile.h"
#include "../../model/tiles.h"
#include "../../utils/error.h"

int main() {
    purple();
    printf("[TEST Tiles 2]\n");
    vec(Tile *) tiles = tiles_from_string("1m2p7s3z");
    vec_free(tiles);
    reset();
}
