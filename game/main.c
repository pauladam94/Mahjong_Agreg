#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../visuals/button.h"
#include "../visuals/utils.h"
#include "raylib.h"
#include <stdio.h>

void test1() {
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

void test2() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Hand *hand = hand_from_string("123m12p112z");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        int tile_pressed = hand_tile_pressed(hand, 200, 200, 0);
        if (tile_pressed != -1) {
            hand_remove_tile(hand, tile_pressed);
        }
        EndDrawing();
    }
    free_tiles_textures();
}

void test3() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Hand *hand = hand_from_string("123m12p112z");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (button_text_is_pressed(100, 500, 50, 100, "DRAW CARD")) {
            hand_add_tile(hand, tile_from_string("1m"));
        }
        int tile_pressed = hand_tile_pressed(hand, 200, 200, 0);
        if (tile_pressed != -1) {
            hand_remove_tile(hand, tile_pressed);
        }
        EndDrawing();
    }
    free_tiles_textures();
}

int main() {
    test3();
    return 0;
}
