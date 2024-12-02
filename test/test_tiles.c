#include "../logic/tiles.h"
#include "../logic/tile.h"
#include "../utils/error.h"

int main() {
	purple();
	printf("=====[TEST Hand]=====\n");
	reset();
	Tiles* tiles = tiles_empty();
	tiles_add_tile(tiles, tile_from_string("1m"));
}
