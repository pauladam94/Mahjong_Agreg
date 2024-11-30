#include "utils.h"
#include "../logic/tile.h"
#include "raylib.h"

#define N_TILE (9 * 3) + 3 + 4

void draw_tile(const Tile *tile, int posX, int posY, int degrees) {
    Texture2D texture = tile_texture(tile);
    DrawTexture(texture, posX, posY, WHITE);
}
