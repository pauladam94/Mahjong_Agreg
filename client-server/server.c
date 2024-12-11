#include "../utils/error.h"
#include <errno.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 500

int server() {
    blue();
    printf("[Server]\n");
    reset();

    struct addrinfo hints, *result, *rp;
    int server_fd;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;     // For binding to all interfaces

    int getaddrinfo_err =
        getaddrinfo(NULL, "8080", &hints, &result); // Resolve server address
    test("Getting Address Info", getaddrinfo_err == 0);
    if (getaddrinfo_err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddrinfo_err));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        printf("--\n");
        server_fd = socket(rp->ai_family, rp->ai_socktype,
                           rp->ai_protocol); // Create socket
        test("Socket Creation", server_fd != -1);
        if (server_fd == -1) {
            continue;
        }

        int enable = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable,
                       sizeof(enable))) {
            perror("setsockopt(SO_REUSEADDR) failed");
        }
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &enable,
                       sizeof(enable))) {
            perror("setsockopt(SO_REUSEADDR) failed");
        }

        // Handle error if socket() fails
        int bin_err = bind(server_fd, rp->ai_addr,
                           rp->ai_addrlen); // Bind socket to address
        test("Bind", bin_err == 0);
        if (bin_err == 0) {
            break;
        } else {
            printf("Bind Error : %s\n", strerror(errno));
        }
        // close(server_fd);
    }

    int listen_err = listen(server_fd, 5); // Listen for incoming connections
    test("Listen Message", listen_err == 0);

    int client_fd = accept(server_fd, NULL, NULL); // Accept a connection
    test("Accept Connection", client_fd != -1);

    // Handle error if accept() fails

    int i = 0;
    while (i++ < 5) {
        char buffer[1024];
        int recv_output = recv(client_fd, buffer, sizeof(buffer),
                               0); // Receive message from client
        test("Receive Message", recv_output != -1);
        printf("Message from client: %s\n", buffer);

        char response[100];
        sprintf(response, "%d : from Server", i);
        int nbytes_send = send(client_fd, response, strlen(response),
                               0); // Send response to client
        test("Send Message", nbytes_send != -1);
    }

    close(client_fd);     // Close client connection
    close(server_fd);     // Close server socket
    freeaddrinfo(result); // Free memory allocated by getaddrinfo
    return 0;
}
