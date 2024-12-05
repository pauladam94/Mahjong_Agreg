#include "../logic/tile.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("=====[TEST Tile 1]=====\n");
    reset();

    Tile *t1 = tile_from_string("1m");
    Tile *t2 = tile_from_string("4p");
    test("1m not same as 4p", !tile_equals(t1, t2));
    tile_free(t1);
    tile_free(t2);
}
