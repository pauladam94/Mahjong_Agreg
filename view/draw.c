#include "draw.h"
#include "../model/hand.h"
#include "../model/tile.h"
#include "../model/tiles.h"
#include "button.h"
#include "raylib.h"
#include "settings.h"
#include "align.h"
#include <stdint.h>
#include <stdlib.h>

const int N_TILE = (3 * 9) + 3 + 4;

static Texture2D *tiles_textures = NULL;
static bool loaded_has_been_done = false;

void load_all_tiles() {
    tiles_textures = calloc(sizeof(*tiles_textures), N_TILE + 1);
    tiles_textures[1] = LoadTexture("data/C1.png");
    tiles_textures[2] = LoadTexture("data/C2.png");
    tiles_textures[3] = LoadTexture("data/C3.png");
    tiles_textures[4] = LoadTexture("data/C4.png");
    tiles_textures[5] = LoadTexture("data/C5.png");
    tiles_textures[6] = LoadTexture("data/C6.png");
    tiles_textures[7] = LoadTexture("data/C7.png");
    tiles_textures[8] = LoadTexture("data/C8.png");
    tiles_textures[9] = LoadTexture("data/C9.png");
    tiles_textures[10] = LoadTexture("data/R1.png");
    tiles_textures[11] = LoadTexture("data/R2.png");
    tiles_textures[12] = LoadTexture("data/R3.png");
    tiles_textures[13] = LoadTexture("data/R4.png");
    tiles_textures[14] = LoadTexture("data/R5.png");
    tiles_textures[15] = LoadTexture("data/R6.png");
    tiles_textures[16] = LoadTexture("data/R7.png");
    tiles_textures[17] = LoadTexture("data/R8.png");
    tiles_textures[18] = LoadTexture("data/R9.png");
    tiles_textures[19] = LoadTexture("data/B1.png");
    tiles_textures[20] = LoadTexture("data/B2.png");
    tiles_textures[21] = LoadTexture("data/B3.png");
    tiles_textures[22] = LoadTexture("data/B4.png");
    tiles_textures[23] = LoadTexture("data/B5.png");
    tiles_textures[24] = LoadTexture("data/B6.png");
    tiles_textures[25] = LoadTexture("data/B7.png");
    tiles_textures[26] = LoadTexture("data/B8.png");
    tiles_textures[27] = LoadTexture("data/B9.png");
    tiles_textures[28] = LoadTexture("data/VE.png");
    tiles_textures[29] = LoadTexture("data/VS.png");
    tiles_textures[30] = LoadTexture("data/VO.png");
    tiles_textures[31] = LoadTexture("data/VN.png");
    tiles_textures[32] = LoadTexture("data/DB.png");
    tiles_textures[33] = LoadTexture("data/DV.png");
    tiles_textures[34] = LoadTexture("data/DR.png");

    for (int i = 1; i <= N_TILE; i++) {
        SetTextureFilter(tiles_textures[i], TEXTURE_FILTER_BILINEAR);
    }
    loaded_has_been_done = true;
}

void tiles_free_textures() {
    for (int i = 1; i <= N_TILE + 1; i++) {
        UnloadTexture(tiles_textures[i]);
    }
    loaded_has_been_done = false;
    free(tiles_textures);
    tiles_textures = NULL;
}

void tile_draw(const Tile *tile, int posX, int posY, Align align) {
    if (!loaded_has_been_done) {
        load_all_tiles();
    }
    Texture2D texture = tiles_textures[(uint64_t)tile];
    Vector2 pos;
    pos.x = posX;
    pos.y = posY;
    float scale = (float)TILE_WIDTH / (float)texture.width;
    float rotation = align_rotation(align);

    DrawTextureEx(texture, pos, rotation, scale, WHITE);
}

Tile *hand_tile_pressed(const Hand *hand, int posX, int posY, Align align) {
    Tiles *closed = hand_closed_tiles(hand);
    for (int i = 0; i < tiles_size(closed); i++) {
        Tile *tile = tiles_get(closed, i);
        int x, y;
        align_pos_hand(align, &x, &y, posX, posY, i);
        tile_draw(tile, x, y, align);
    }

    Tiles *discarded = hand_discarded_tiles(hand);
    for (int i = 0; i < tiles_size(discarded); i++) {
        Tile *tile = tiles_get(discarded, i);
        int x, y;
        align_pos_discard(align, &x, &y, posX, posY, i);
        tile_draw(tile, x, y, align);
    }
    for (int i = 0; i < tiles_size(closed); i++) {
        Tile *tile = tiles_get(closed, i);
        int x, y;
        align_pos_hand(align, &x, &y, posX, posY, i);
        if (button_is_pressed(x, y, TILE_WIDTH, TILE_HEIGHT, align)) {
            return tile;
        }
    }

    return NULL;
}
