#include "../utils/error.h"
#include "../view/client.h"
#include "../view/server.h"
#include "raylib.h"
#include "../utils/raygui.h"

void start_menu(void) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);

        if (GuiButton((Rectangle){100, 100, 100, 100}, "Server")) {
            // Multithread this server for sure.
            test(launch_server() == 0, "Lauch Server");
            // Run Also the client here
            run_server();
        }

        if (GuiButton((Rectangle){100, 300, 100, 100}, "Client")) {
            test(launch_client() == 0, "Lauch Client");
            client();
        }
        EndDrawing();
    }
}
