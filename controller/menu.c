#include "../utils/raygui.h"
#include "../view/client.h"
#include "../view/server.h"
#include "raylib.h"

void start_menu(void) {

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (GuiButton((Rectangle){100, 100, 100, 100}, "Server")) {

            // Multithread this thing potentially
            launch_server();
            // Run Also the client here
        }

        if (GuiButton((Rectangle){100, 300, 100, 100}, "Client")) {
            launch_client();
        }
        EndDrawing();
    }
}
