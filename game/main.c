#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../visuals/utils.h"
#include "raylib.h"
#include <stdio.h>
#include "../visuals/button.h"

int test1() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Tile *tile = tile_from_string("7m");
    Hand *hand = hand_from_string("123m12p1z");
    Hand *hand2 = hand_from_string("123m12p112z");
    pp_tile(stdout, tile);
    printf("\n");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        draw_tile(tile, 100, 100, 90);
        draw_hand(hand, 200, 200, 0);
        draw_hand(hand2, 500, 500, 10);

        hand_tile_pressed(hand2, 800, 800, 0);
        bool result = button_is_pressed(100, 100, 200, 200);
        EndDrawing();
    }
    free_tiles_textures();
}


int main() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Tile *tile = tile_from_string("7m");
    Hand *hand = hand_from_string("123m12p1z");
    Hand *hand2 = hand_from_string("123m12p112z");
    pp_tile(stdout, tile);
    printf("\n");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        draw_tile(tile, 100, 100, 90);
        draw_hand(hand, 200, 200, 0);
        draw_hand(hand2, 500, 500, 10);

        hand_tile_pressed(hand2, 800, 800, 0);
        bool result = button_is_pressed(100, 100, 200, 200);
        EndDrawing();
    }
    free_tiles_textures();
}
