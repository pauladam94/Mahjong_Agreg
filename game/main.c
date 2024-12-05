#include "../client/client.h"
#include "../client/server.h"
#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "../visuals/button.h"
#include "../visuals/draw.h"
#include "../visuals/settings.h"
#include "../visuals/setup.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum Player { Player0, Player1, Player2, Player3 } Player;

void test_game() {
    setup_window();

    char buff[100];
    Tiles *tiles = tiles_all();
    Player player = Player0;
    int x, y = 0;
    float rotation = 10.;
    Vector2 origin;
    origin.x = (float)WIDTH / 2;
    origin.y = (float)HEIGHT / 2;
    Align align = DOWN;

    Hand *hands[4];
    for (int i = 0; i < 4; i++) {
        hands[i] = hand_draw_from(tiles, 13);
        hand_sort(hands[i]);
    }

    while (!WindowShouldClose()) {
        rotation += 0.5;
        BeginDrawing();
        ClearBackground(WHITE);

        // hand_add_tile(hands[0], tile_random());
        // hand_sort(hands[0]);

        sprintf(buff, "Turn : %d", player);
        DrawText(buff, TILE_WIDTH * 2, HEIGHT - TILE_HEIGHT, 20, BLACK);
        sprintf(buff, "Tile remaining %d", tiles_size(tiles));
        DrawText(buff, TILE_WIDTH * 2, HEIGHT - 1.5 * TILE_HEIGHT, 20, BLACK);

        if (hand_is_complete(hands[0])) {
            DrawText("Hand is Complete", TILE_WIDTH * 2,
                     HEIGHT - TILE_HEIGHT / 2, 20, BLACK);
        } else {
            DrawText("Hand is not Complete", TILE_WIDTH * 2,
                     HEIGHT - TILE_HEIGHT / 2, 20, BLACK);
        }

        for (Player i = Player0; i <= Player3; i++) {
            switch (i) {
            case Player0:
                x = WIDTH / 2 - 7 * TILE_WIDTH;
                y = HEIGHT - TILE_HEIGHT;
                break;
            case Player1:
                x = WIDTH - TILE_HEIGHT;
                y = HEIGHT / 2 + 7 * TILE_WIDTH;
                break;
            case Player2:
                x = WIDTH / 2 - 7 * TILE_WIDTH;
                y = TILE_HEIGHT;
                break;
            case Player3:
                x = TILE_HEIGHT;
                y = HEIGHT / 2 - 7 * TILE_WIDTH;
                break;
            }
            switch (i) {
            case Player0:
                align = DOWN;
                break;
            case Player1:
                align = RIGHT;
                break;
            case Player2:
                align = UP;
                break;
            case Player3:
                align = LEFT;
                break;
            }

            Tile *tile_pressed = hand_tile_pressed(hands[i], x, y, align);
            if (tile_pressed != NULL && i == player) {
                hand_discard_tile(hands[i], tile_pressed);

                player = (player + 1) % 4;

                Tile *random_tile = tiles_random_from(tiles);
                hand_add_tile(hands[player], random_tile);
                tiles_remove_equals(tiles, random_tile);
                hand_sort(hands[player]);
            }
        }
        EndDrawing();
    }
    for (int i = 0; i < 4; i++) {
        hand_free(hands[i]);
    }
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
