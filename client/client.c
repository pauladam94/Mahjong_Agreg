#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 500

int client(int id) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;     // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP

    getaddrinfo("127.0.0.1", "8080", &hints, &res); // Resolve server address
    // Handle error if getaddrinfo() fails

    int client_fd = socket(res->ai_family, res->ai_socktype,
                           res->ai_protocol); // Create socket
    // Handle error if socket() fails

    connect(client_fd, res->ai_addr, res->ai_addrlen); // Connect to server
    // Handle error if connect() fails

    const char *message = "Hello from client!";
    send(client_fd, message, strlen(message), 0); // Send message to server

    char buffer[1024];
    recv(client_fd, buffer, sizeof(buffer), 0); // Receive response from server
    printf("Message from server: %s\n", buffer);

    close(client_fd);  // Close connection
    freeaddrinfo(res); // Free memory allocated by getaddrinfo
    return 0;
    ///////////////////////////////////////////////////
}

int client2() {
    printf("Run Client\n");
    char *argv[] = {"client", "host_paul", "8090", "my message"};
    int argc = 3;
    int sfd, s;
    char buf[BUF_SIZE];
    size_t len;
    ssize_t nread;
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("host : %s\n", argv[1]);
    printf("port : %s\n", argv[2]);
    printf("msg : %s\n", argv[3]);

    /* Obtain address(es) matching host/port. */

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0; /* Any protocol */

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break; /* Success */

        close(sfd);
    }

    freeaddrinfo(result); /* No longer needed */

    if (rp == NULL) { /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }

    /* Send remaining command-line arguments as separate
       datagrams, and read responses from server. */

    for (size_t j = 3; j < argc; j++) {
        len = strlen(argv[j]) + 1;
        /* +1 for terminating null byte */

        if (len > BUF_SIZE) {
            fprintf(stderr, "Ignoring long message in argument %zu\n", j);
            continue;
        }

        if (write(sfd, argv[j], len) != len) {
            fprintf(stderr, "partial/failed write\n");
            exit(EXIT_FAILURE);
        }

        nread = read(sfd, buf, BUF_SIZE);
        if (nread == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Received %zd bytes: %s\n", nread, buf);
    }

    exit(EXIT_SUCCESS);
}
