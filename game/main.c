#include "../visuals/utils.h"
#include "../logic/tile.h"
#include "raylib.h"
#include <stdio.h>

int main() {
    InitWindow(1920, 1080, "MahJong Agreg");
    SetTargetFPS(60);
    Tile *m1 = tile_from_string("4m");
	pp_tile(stdout, m1);
	pp_tile(stdout, m1);
	pp_tile(stdout, m1);
	printf("--------------------------\n\n");
	// pp_tile(stdout);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        draw_tile(m1, 100, 100, 90);
        EndDrawing();
    }
}
