#include "raylib.h"

int main() {
	InitWindow(1000, 1000, "MahJong Agreg");
	SetTargetFPS(60);
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GREEN);
		EndDrawing();
	}
}
