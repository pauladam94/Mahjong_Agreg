#include "../client/client.h"
#include "../client/server.h"
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
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void test_game(int argc, char **argv) {
    setup_window();

    char buff[100];
    vec(Tile *) tiles = tiles_all();
    vec(Tile *) dead_wall = NULL;
    for (int i = 0; i < 14; i++) {
        vec_push(dead_wall, tiles_pick_from(tiles));
    }

    Vector2 origin;
    origin.x = (float)WIDTH / 2;
    origin.y = (float)HEIGHT / 2;

    Hands *hands = hands_empty();
    hands_pick_from(hands, tiles);
    // First player has one more tile to begin the game
    hand_pick_from(hands_get(hands, Player0), tiles);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        sprintf(buff, "\nRemaining : %lu", vec_len(tiles));
        DrawText(buff, WIDTH / 2 - 2 * TILE_WIDTH, HEIGHT / 2, 20, BLACK);
        if (hand_is_complete(hands_get(hands, Player0))) {
            DrawText("Hand Complete", TILE_WIDTH * 2, HEIGHT - TILE_HEIGHT / 2,
                     20, BLACK);
        } else {
            DrawText("Hand Not Complete", TILE_WIDTH * 2,
                     HEIGHT - TILE_HEIGHT / 2, 20, BLACK);
        }

        hands_draw(hands);
        Context ctx = context_get();
        hands_update(hands, tiles, ctx);
        EndDrawing();
    }
    hands_free(hands);
    vec_free(tiles);
    tiles_free_textures();
}

int client_server(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s id(between 1 and 4)\n", argv[0]);
    }
    int id = atoi(argv[1]);
    if (id == 1) {
        return server();
    } else {
        return client(0);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    test_game(argc, argv);
    return 0;
}
