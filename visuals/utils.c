#include "utils.h"
#include "../logic/tiles.h"
#include "../logic/tile.h"
#include "raylib.h"
#include "button.h"

#define N_TILE (9 * 3) + 3 + 4

int tiles_tile_pressed(const Tiles *tiles, int posX, int posY, int degrees) {
    draw_tiles(tiles, posX, posY, degrees);
    for (int i = 0; i < tiles_size(tiles); i++) {
        Tile *tile = get_tile(tiles, i);
        Texture2D texture = tile_texture(tile);
        int height = texture.height;
        int width = texture.width;

        int tilePosX = posX + i * texture.width;

        DrawTexture(texture, tilePosX, posY, WHITE);
        if (button_is_pressed(tilePosX, posY, width, height)) {
            return i;
        }
    }
    return -1;
}

void draw_tiles(const Tiles *tiles, int posX, int posY, int degrees) {
    for (int i = 0; i < tiles_size(tiles); i++) {
        Tile *tile = get_tile(tiles, i);
        Texture2D texture = tile_texture(tile);
        DrawTexture(texture, posX + i * texture.width, posY, WHITE);
    }
}

void draw_tile(const Tile *tile, int posX, int posY, int degrees) {
    Texture2D texture = tile_texture(tile);
    DrawTexture(texture, posX, posY, WHITE);
}
