#include "../model/tile.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Tile 1]\n");
    reset();

    Tile *t1 = tile_from_string("1m");
    Tile *t2 = tile_from_string("4p");
    test(!tile_equals(t1, t2), "1m not same as 4p");
}
