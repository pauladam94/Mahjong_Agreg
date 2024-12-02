#include "../logic/tile.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("=====[TEST Tile]=====\n");
    reset();

    test("1m not same as 4p",
         !tile_equals(tile_from_string("1m"), tile_from_string("4p")));
}
