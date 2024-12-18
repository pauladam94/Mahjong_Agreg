#include "setup.h"
#include "raylib.h"
#include "settings.h"
#include <stdlib.h>
#include <time.h>

void setup_window(Settings settings) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // FLAG_FULLSCREEN_MODE
    InitWindow(settings.width, settings.height, "MahJong Agreg");
    SetTargetFPS(60);

    srand(time(NULL));
}
