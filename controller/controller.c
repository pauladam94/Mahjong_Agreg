#include "../model/hand.h"
#include "../model/hands.h"
#include "../model/player.h"
#include "../model/tile.h"
#include "../model/tiles.h"
#include "../utils/vec.h"
#include "../view/context.h"
#include "../view/draw.h"
#include "../view/settings.h"
#include "../view/setup.h"
#include "gui.h"
#include "menu.h"
#include "raylib.h"
#include "../utils/raygui.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void game() {
    Settings settings = settings_init(1920, 1080);

    setup_window(settings);
    RenderTexture2D target = LoadRenderTexture(1920, 1080);

    Game game = game_empty();
    // start_menu(&game);

    char buff[100];
    vec(Tile *) tiles = tiles_all();
    vec(Tile *) dead_wall = NULL;
    for (int i = 0; i < 14; i++) {
        vec_push(dead_wall, tiles_pick_from(&tiles));
    }

    Hands *hands = hands_empty(settings);
    hands_pick_from(hands, &tiles, settings);
    // First player has one more tile to begin the game
    hand_pick_from(hands_get(hands, Player0), &tiles, settings);

    while (!WindowShouldClose()) {

        BeginTextureMode(target);
        ClearBackground(WHITE);
        DrawRectangleRec((Rectangle){0, 0, 100, 100}, RED);

        zoom_gui();


        sprintf(buff, "\nRemaining : %lu", vec_len(tiles));
        DrawText(buff, settings.width / 2 - 2 * settings.tile_width,
                 settings.height / 2, 20, BLACK);
        if (hand_is_complete(hands_get(hands, Player0))) {
            DrawText("Hand Complete", settings.tile_width * 2,
                     settings.height - settings.tile_height / 2, 20, BLACK);
        } else {
            DrawText("Hand Not Complete", settings.tile_width * 2,
                     settings.height - settings.tile_height / 2, 20, BLACK);
        }
        hands_draw(hands, settings);
        Context ctx = context_get();
        hands_update(hands, &tiles, ctx, settings);
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            target.texture,
            (Rectangle){0, 0, target.texture.width, -target.texture.height},
            (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
            (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();
    }
    hands_free(hands);
    vec_free(tiles);
    vec_free(dead_wall);
    tiles_free_textures();
    UnloadRenderTexture(target);
}

int main() {
    game();
    return 0;
}
