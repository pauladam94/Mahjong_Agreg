#include "raylib.h"
#include "settings.h"
#include <stdlib.h>
#include <time.h>

void setup_window(void) {
    InitWindow(WIDTH, HEIGHT, "MahJong Agreg");
    SetTargetFPS(60);

    srand(time(NULL));
}
