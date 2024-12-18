#include "menu.h"
#include "../model/game.h"
#include "../utils/error.h"
#include "../utils/raygui.h"
#include "../view/client.h"
#include "../view/server.h"
#include "raylib.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

void *start_menu(Game *game) {
    pthread_t server_thread, client_thread;
    bool server_launched = false;
    bool client_launched = false;
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);

        if (!server_launched &&
            GuiButton((Rectangle){100, 100, 100, 100}, "Server")) {
            // Multithread this server for sure.
            test(launch_server() == 0, "Lauch Server");
            // Run Also the client here
            // run_server();
            //
            test(pthread_create(&server_thread, NULL, run_server, NULL) == 0,
                 "Server thread created");
            server_launched = true;
        }

        if (GuiButton((Rectangle){100, 300, 100, 100}, "Client")) {
            test(launch_client() == 0, "Lauch Client");
            test(pthread_create(&client_thread, NULL, client, game) == 0,
                 "Client thread created");
            client_launched = true;
        }
        EndDrawing();
        if (client_launched) {
            break;
        }
    }
    return NULL;
}
