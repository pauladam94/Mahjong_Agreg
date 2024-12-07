#include "draw.h"
#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "button.h"
#include "raylib.h"
#include "settings.h"

#define N_TILE (9 * 3) + 3 + 4

void draw_tile(const Tile *tile, int posX, int posY, Align align) {
    Texture2D texture = tile_texture(tile);
    Vector2 pos;
    pos.x = posX;
    pos.y = posY;
    float scale = (float)TILE_WIDTH / (float)texture.width;
    float rotation = align_rotation(align);

    DrawTextureEx(texture, pos, rotation, scale, WHITE);
}

/*
void draw_tiles(const Tiles *tiles, int posX, int posY, Align align) {
    for (int i = 0; i < tiles_size(tiles); i++) {
        Tile *tile = tiles_get(tiles, i);
        int x, y = 0;
        switch (align) {
        case DOWN:
            x = posX + i * TILE_WIDTH;
            y = posY;
            break;
        case RIGHT:
            x = posX;
            y = posY - i * TILE_WIDTH;
            break;
        case UP:
            x = posX + i * TILE_WIDTH;
            y = posY;
            break;
        case LEFT:
            x = posX;
            y = posY + i * TILE_WIDTH;
            break;
        }
        draw_tile(tile, x, y, align);
    }
}
*/

Tile *hand_tile_pressed(const Hand *hand, int posX, int posY, Align align) {
    Tiles *closed = hand_closed_tiles(hand);
    for (int i = 0; i < tiles_size(closed); i++) {
        Tile *tile = tiles_get(closed, i);
        int x, y;
        switch (align) {
        case DOWN:
            x = posX + i * TILE_WIDTH;
            y = posY;
            break;
        case RIGHT:
            x = posX;
            y = posY - i * TILE_WIDTH;
            break;
        case UP:
            x = posX + i * TILE_WIDTH;
            y = posY;
            break;
        case LEFT:
            x = posX;
            y = posY + i * TILE_WIDTH;
            break;
        }
        draw_tile(tile, x, y, align);
    }

    Tiles *discarded = hand_discarded_tiles(hand);
    for (int i = 0; i < tiles_size(discarded); i++) {
        Tile *tile = tiles_get(discarded, i);
        int x, y;
        switch (align) {
        case DOWN:
            x = posX + (i % 6) * TILE_WIDTH + 3 * TILE_WIDTH;
            y = posY + (i / 6) * TILE_HEIGHT - 4 * TILE_HEIGHT;
            break;
        case RIGHT:
            x = posX + (i / 6) * TILE_HEIGHT - 4 * TILE_HEIGHT;
            y = posY - (i % 6) * TILE_WIDTH - 3 * TILE_WIDTH;
            break;
        case UP:
            x = posX - (i % 6) * TILE_WIDTH + 10 * TILE_WIDTH;
            y = posY - (i / 6) * TILE_HEIGHT + 4 * TILE_HEIGHT;
            break;
        case LEFT:
            x = posX - (i / 6) * TILE_HEIGHT + 4 * TILE_HEIGHT;
            y = posY + (i % 6) * TILE_WIDTH + 3 * TILE_WIDTH;
            break;
        }
        draw_tile(tile, x, y, align);
    }
    for (int i = 0; i < tiles_size(closed); i++) {
        Tile *tile = tiles_get(closed, i);
        int height = TILE_HEIGHT;
        int width = TILE_WIDTH;
        int x, y;
        switch (align) {
        case DOWN:
            x = posX + i * TILE_WIDTH;
            y = posY;
            break;
        case RIGHT:
            x = posX;
            y = posY - i * TILE_WIDTH;
            break;
        case UP:
            x = posX + i * TILE_WIDTH;
            y = posY;
            break;
        case LEFT:
            x = posX;
            y = posY + i * TILE_WIDTH;
            break;
        }
        if (button_is_pressed(x, y, width, height, align)) {
            return tile_copy(tile);
        }
    }

    return NULL;
}
