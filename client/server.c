#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 500

int server() {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;     // For binding to all interfaces

    getaddrinfo(NULL, "8080", &hints, &res); // Resolve server address
    // Handle error if getaddrinfo() fails

    int server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); // Create socket
    // Handle error if socket() fails

    bind(server_fd, res->ai_addr, res->ai_addrlen); // Bind socket to address
    // Handle error if bind() fails

    listen(server_fd, 5); // Listen for incoming connections
    // Handle error if listen() fails

    int client_fd = accept(server_fd, NULL, NULL); // Accept a connection
    // Handle error if accept() fails

    char buffer[1024];
    recv(client_fd, buffer, sizeof(buffer), 0); // Receive message from client
    printf("Message from client: %s\n", buffer);

    const char* response = "Hello from server!";
    send(client_fd, response, strlen(response), 0); // Send response to client

    close(client_fd); // Close client connection
    close(server_fd); // Close server socket
    freeaddrinfo(res); // Free memory allocated by getaddrinfo
    return 0;
}

int server2() {

    printf("Run Server\n");
    char *argv[] = {"server", "host_paul"};
    int argc = 2;
    int sfd, s;
    char buf[BUF_SIZE];
    ssize_t nread;
    socklen_t peer_addrlen;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    struct sockaddr_storage peer_addr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("port : %s\n", argv[1]);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; // SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(NULL, argv[1], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully bind(2).
       If socket(2) (or bind(2)) fails, we (close the socket
       and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; /* Success */

        close(sfd);
    }

    freeaddrinfo(result); /* No longer needed */

    if (rp == NULL) { /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    /* Read datagrams and echo them back to sender. */

    for (;;) {
        char host[NI_MAXHOST], service[NI_MAXSERV];

        peer_addrlen = sizeof(peer_addr);
        nread = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *)&peer_addr,
                         &peer_addrlen);
        if (nread == -1)
            continue; /* Ignore failed request */

        s = getnameinfo((struct sockaddr *)&peer_addr, peer_addrlen, host,
                        NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
        if (s == 0)
            printf("Received %zd bytes from %s:%s\n", nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

        if (sendto(sfd, buf, nread, 0, (struct sockaddr *)&peer_addr,
                   peer_addrlen) != nread) {
            fprintf(stderr, "Error sending response\n");
        }
    }
}
