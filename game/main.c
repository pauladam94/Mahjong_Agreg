#include "../client/client.h"
#include "../client/server.h"
#include "../logic/hand.h"
#include "../logic/hands.h"
#include "../logic/player.h"
#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "../view/button.h"
#include "../view/draw.h"
#include "../view/settings.h"
#include "../view/setup.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void test_game() {
    setup_window();

    char buff[100];
    Tiles *tiles = tiles_all();
    Player current_player = Player0;
    int x, y = 0;
    Vector2 origin;
    origin.x = (float)WIDTH / 2;
    origin.y = (float)HEIGHT / 2;
    Align align = DOWN;

    Hands *hands = hands_empty();
    hands_draw_from(hands, tiles);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        sprintf(buff, "\nRemaining : %d", tiles_size(tiles));
        DrawText(buff, WIDTH / 2 - 2 * TILE_WIDTH, HEIGHT / 2, 20, BLACK);

        if (hand_is_complete(hands_get(hands, Player0))) {
            DrawText("Hand Complete", TILE_WIDTH * 2, HEIGHT - TILE_HEIGHT / 2,
                     20, BLACK);
        } else {
            DrawText("Hand Not Complete", TILE_WIDTH * 2,
                     HEIGHT - TILE_HEIGHT / 2, 20, BLACK);
        }
        for (Player player = Player0; player <= Player3; player++) {
            player_position(player, &x, &y);
            player_align(player, &align);

            Tile *tile_pressed;
            tile_pressed =
                hand_tile_pressed(hands_get(hands, player), x, y, align);
            if (player != Player0) {
                tile_pressed = tiles_random_from(
                    hand_closed_tiles(hands_get(hands, player)));
            }
            if (tile_pressed != NULL && player == current_player) {
                hand_discard_tile(hands_get(hands, player), tile_pressed);

                current_player = (current_player + 1) % 4;

                Tile *random_tile = tiles_random_from(tiles);
                hand_add_tile(hands_get(hands, player), random_tile);
                tiles_remove_equals(tiles, random_tile);
                hand_sort(hands_get(hands, player));
                if (current_player == Player0) {
                    sleep(1);
                }
            }
        }
        EndDrawing();
    }

    hands_free(hands);

    tiles_free(tiles);
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
    test_game();
    return 0;
}
