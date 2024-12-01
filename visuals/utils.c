#include "utils.h"
#include "../logic/hand.h"
#include "../logic/tile.h"
#include "raylib.h"
#include "button.h"

#define N_TILE (9 * 3) + 3 + 4

int hand_tile_pressed(const Hand *hand, int posX, int posY, int degrees) {
    draw_hand(hand, posX, posY, degrees);
    for (int i = 0; i < hand_size(hand); i++) {
        Tile *tile = get_tile(hand, i);
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

void draw_hand(const Hand *hand, int posX, int posY, int degrees) {
    for (int i = 0; i < hand_size(hand); i++) {
        Tile *tile = get_tile(hand, i);
        Texture2D texture = tile_texture(tile);
        DrawTexture(texture, posX + i * texture.width, posY, WHITE);
    }
}

void draw_tile(const Tile *tile, int posX, int posY, int degrees) {
    Texture2D texture = tile_texture(tile);
    DrawTexture(texture, posX, posY, WHITE);
}
