#include "utils.h"
#include "../logic/tile.h"
#include "raylib.h"
#include <stdbool.h>

void draw_tile(const Tile *tile, int posX, int posY, int degrees) {
	Image image = tile_image(tile);
	Texture2D texture = LoadTextureFromImage(image);
    DrawTexture(texture, posX, posY, WHITE);
}
