#include "client.h"
#include "../model/game.h"
#include "../utils/error.h"
#include "../utils/pp.h"
#include "msg.h"
#include "pthread.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static int client_client_fd;

int launch_client() {
    blue();
    printf("[Client]\n");
    reset();
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    int getaddrinfo_err = getaddrinfo("127.0.0.1", "8080", &hints,
                                      &result); // Resolve server address
    test(getaddrinfo_err == 0, "Getting Address Info");
    if (getaddrinfo_err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddrinfo_err));
        exit(EXIT_FAILURE);
    }

    client_client_fd = socket(result->ai_family, result->ai_socktype,
                              result->ai_protocol); // Create socket
    test(client_client_fd != -1, "Socket creation");

    int connect_output = connect(client_client_fd, result->ai_addr,
                                 result->ai_addrlen); // Connect to server
    test(connect_output == 0, "Connection");
    freeaddrinfo(result); // Free memory allocated by getaddrinfo
    return 0;
}

void *client_recv(void *arg) {
    Game *game = (Game *)arg;
    Msg msg;
    while (true) {
        int recv_output = msg_recv(client_client_fd, &msg);
        test(recv_output != -1, "Receive Message");
        fppf(stdout, "Msg from server: %a\n", &msg_pp, &msg);

        switch (msg.type) {
        case EVENT:
            game_push_event(game, msg.event);
            break;
        default:
            printf("TODO other type client_rcv\n");
            break;
        }
    }
}

void *client(void *arg) {
    Game *game = (Game *)arg;
    Msg msg;

    int recv_output = msg_recv(client_client_fd, &msg);
    test(recv_output != -1, "Receive Initial Message");
    fppf(stdout, "Msg from server: %a\n", &msg_pp, &msg);

    if (msg.type == SET_PLAYER_NUMBER) {
        game->player = msg.set_player_number.player;
        printf("Player Number set to : %d\n", (int)game->player);
    }

    pthread_t client_recv_thread_id;
    test(pthread_create(&client_recv_thread_id, NULL, client_recv, game) == 0,
         "Client Recv thread created");

    // Client Send Thread
    while (true) {
        pthread_mutex_lock(&game->events_to_send_mutex);
        if (pthread_cond_wait(&game->events_to_send_cond,
                              &game->events_to_send_mutex) == NULL) {
            
        }

        pthread_mutex_unlock(&game->events_to_send_mutex);
    }

    close(client_client_fd); // Close connection
    return NULL;
}
