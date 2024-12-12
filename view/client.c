#include "../utils/error.h"
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 500

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
    test("Getting Address Info", getaddrinfo_err == 0);
    if (getaddrinfo_err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddrinfo_err));
        exit(EXIT_FAILURE);
    }

    client_client_fd = socket(result->ai_family, result->ai_socktype,
                              result->ai_protocol); // Create socket
    test("Socket creation", client_client_fd != -1);

    int connect_output = connect(client_client_fd, result->ai_addr,
                                 result->ai_addrlen); // Connect to server
    test("Connection", connect_output == 0);
    freeaddrinfo(result); // Free memory allocated by getaddrinfo
    return 0;
}

int client() {

    int i = 0;
    while (i++ < 5) {
        char message[30];
        sprintf(message, "%d : from Client", i);
        int nbytes_send = send(client_client_fd, message, strlen(message),
                               0); // Send message to server
        test("Send Message", nbytes_send != -1);

        char buffer[1024];
        int recv_output = recv(client_client_fd, buffer, sizeof(buffer),
                               0); // Receive response from server
        test("Receive Message", recv_output != -1);
        printf("Message from server: %s\n", buffer);

        sleep(2);
    }

    close(client_client_fd); // Close connection
    return 0;
}
