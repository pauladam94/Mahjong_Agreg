#include "../model/tile.h"
#include "../model/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Tiles 1]\n");
    reset();
    vec(Tile *) tiles = NULL;
    // #pragma clang diagnostic push
    // #pragma clang diagnostic ignored "-WarnOnSizeOfPointerToAggregate"
    // bugprone-sizeof-expression
    vec_push(tiles, tile_from_string("1m"));
    // #pragma clang diagnostic pop
    tiles_pp(stdout, tiles);
    printf("\n");
    vec_free(tiles);
}
