#include "../logic/tiles.h"
#include "../logic/tile.h"

int main() {
	printf("In TEST tiles\n");
	Tiles* tiles = empty_tiles();
	tiles_add_tile(tiles, tile_from_string("1m"));
}
