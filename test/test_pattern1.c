#include "../model/pattern.h"
#include "../model/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Pattern 1]\n");
    Pattern * pat = pattern_from_tiles(tiles_from_string("111m12345p1214s12z"));
    pattern_free(pat);
}
