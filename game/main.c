#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "../visuals/button.h"
#include "../visuals/draw.h"
#include "raylib.h"
#include <stdio.h>

void test1() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Tile *tile = tile_from_string("7m");
    Tiles *tiles = tiles_from_string("123m12p1z");
    Tiles *tiles2 = tiles_from_string("123m12p112z");
    tile_pp(stdout, tile);
    printf("\n");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        draw_tile(tile, 100, 100, 90);
        draw_tiles(tiles, 200, 200, 0);
        draw_tiles(tiles2, 500, 500, 10);

        tiles_tile_pressed(tiles2, 800, 800, 0);
        bool result = button_is_pressed(100, 100, 200, 200);
        EndDrawing();
    }
    tiles_free_textures();
}

void test2() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Tiles *tiles = tiles_from_string("123m12p112z");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        int tile_pressed = tiles_tile_pressed(tiles, 200, 200, 0);
        if (tile_pressed != -1) {
            tiles_remove(tiles, tile_pressed);
        }
        EndDrawing();
    }
    tiles_free_textures();
}

void test3() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Tiles *tiles = tiles_from_string("123m12p112z");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (button_text_is_pressed(100, 500, 50, 100, "DRAW CARD")) {
            tiles_add(tiles, tile_from_string("1m"));
        }
        int tile_pressed = tiles_tile_pressed(tiles, 200, 200, 0);
        if (tile_pressed != -1) {
            tiles_remove(tiles, tile_pressed);
        }
        EndDrawing();
    }
    tiles_free_textures();
}

void test4() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Tiles *tiles = tiles_from_string("123m12p112z");
    bool should_draw = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (button_text_is_pressed(100, 500, 140, 40, "DRAW CARD") &&
            should_draw) {
            tiles_add(tiles, tile_from_string("1m"));
            should_draw = false;
        }

        if (should_draw) {
            DrawText("You should draw a Card", 100, 100, 20, BLACK);
        } else {
            DrawText("You should Delete a Card", 100, 100, 20, BLACK);
        }

        int tile_pressed = tiles_tile_pressed(tiles, 200, 200, 0);
        if (tile_pressed != -1 && !should_draw) {
            tiles_remove(tiles, tile_pressed);
            should_draw = true;
        }
        EndDrawing();
    }
    tiles_free(tiles);
}

void test5() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Hand *hand = hand_from_string("7z12m1p12z2m7p");
    hand_sort(hand);
    bool should_draw = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (button_text_is_pressed(100, 500, 140, 40, "DRAW CARD") &&
            should_draw) {
            hand_add_tile(hand, tile_random());
            hand_sort(hand);
            should_draw = false;
        }

        if (should_draw) {
            DrawText("You should draw a Card", 100, 100, 20, BLACK);
        } else {
            DrawText("You should Delete a Card", 100, 100, 20, BLACK);
        }

        int tile_pressed = hand_tile_pressed(hand, 200, 200, 0);
        if (tile_pressed != -1 && !should_draw) {
            hand_remove_tile(hand, tile_pressed);
            should_draw = true;
        }
        EndDrawing();
    }
    hand_free(hand);
}

int main() {
    test5();
    return 0;
}
