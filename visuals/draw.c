#include "draw.h"
#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "button.h"
#include "raylib.h"

#define N_TILE (9 * 3) + 3 + 4

int hand_tile_pressed(const Hand *hand, int posX, int posY, int degrees) {
    draw_tiles(hand_closed_tiles(hand), posX, posY, degrees);
    for (int i = 0; i < tiles_size(hand_closed_tiles(hand)); i++) {
        Tile *tile = tiles_get(hand_closed_tiles(hand), i);
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

int tiles_tile_pressed(const Tiles *tiles, int posX, int posY, int degrees) {
    draw_tiles(tiles, posX, posY, degrees);
    for (int i = 0; i < tiles_size(tiles); i++) {
        Tile *tile = tiles_get(tiles, i);
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
        Tile *tile = tiles_get(tiles, i);
        Texture2D texture = tile_texture(tile);
        DrawTexture(texture, posX + i * texture.width, posY, WHITE);
    }
}

void draw_tile(const Tile *tile, int posX, int posY, int degrees) {
    Texture2D texture = tile_texture(tile);
    Vector2 pos;
    pos.x = posX;
    pos.y = posY;
    DrawTextureEx(texture, pos, degrees, 1., WHITE);
}
