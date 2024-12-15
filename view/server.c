#include "../utils/better_int.h"
#include "../utils/error.h"
#include "../utils/pp.h"
#include "../utils/vec.h"
#include "msg.h"
#include "poll.h"
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

const int SERVER = 0;
vec(struct pollfd) fds = NULL;

int launch_server() {
    struct pollfd empty_poll_fd = {0};
    struct addrinfo hints, *result, *rp;

    vec_push(fds, empty_poll_fd); // Only the server in fds at the beginning

    // Initialize the pollfd structure
    fds[SERVER].events = POLLIN; // Monitor for incoming connections

    blue();
    printf("[Server]\n");
    reset();

    // memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;     // For binding to all interfaces

    int getaddrinfo_err =
        getaddrinfo(NULL, "8080", &hints, &result); // Resolve server address
    test(getaddrinfo_err == 0, "Getting Address Info");
    if (getaddrinfo_err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(getaddrinfo_err));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        printf("--\n");
        fds[SERVER].fd = socket(rp->ai_family, rp->ai_socktype,
                                rp->ai_protocol); // Create socket
        test(fds[SERVER].fd != -1, "Socket Creation");
        if (fds[SERVER].fd == -1) {
            continue;
        }

        int enable = 1;
        if (setsockopt(fds[SERVER].fd, SOL_SOCKET, SO_REUSEADDR, &enable,
                       sizeof(enable))) {
            perror("setsockopt(SO_REUSEADDR) failed");
        }
        if (setsockopt(fds[SERVER].fd, SOL_SOCKET, SO_REUSEPORT, &enable,
                       sizeof(enable))) {
            perror("setsockopt(SO_REUSEADDR) failed");
        }

        // Handle error if socket() fails
        int bin_err = bind(fds[SERVER].fd, rp->ai_addr,
                           rp->ai_addrlen); // Bind socket to address
        test(bin_err == 0, "Bind");
        if (bin_err == 0) {
            break;
        } else {
            printf("Bind Error : %s\n", strerror(errno));
        }
        close(fds[SERVER].fd);
    }

    int listen_err =
        listen(fds[SERVER].fd, 5); // Listen for incoming connections
    test(listen_err == 0, "Listen Incoming Connection");
    freeaddrinfo(result); // Free memory allocated by getaddrinfo
    return 0;
}

// TREAT INCOMING CONNECTION
int run_server() {
    u64 cpt_poll = 0;
    struct pollfd empty_poll_fd = {0};
    while (true) {
        cpt_poll++;
        int activity =
            poll(fds, vec_len(fds), -1); // Wait indefinitely for activity
        test(activity != -1, "Poll %d", cpt_poll);
        if (activity == -1) {
            perror("Poll error");
            continue;
        }

        // Check for new connection
        if (fds[SERVER].revents & POLLIN) {
            int fd = accept(fds[SERVER].fd, NULL, NULL);

            empty_poll_fd.fd = fd;
            empty_poll_fd.events = POLLIN; // Monitor for incoming data
            vec_push(fds, empty_poll_fd);  // Accept a connection

            test(fds[vec_len(fds) - 1].fd != -1, "Accept Connection N°%d",
                 vec_len(fds) - 1);
            if (fds[vec_len(fds) - 1].fd == -1) {
                vec_pop(fds);
            }
        }
        Msg msg;

        // Check for new messages
        for (u64 i = 1; i < vec_len(fds); i++) {
            if (fds[i].revents & POLLIN) {

                // Receive Message
                int recv_output = msg_recv(fds[i].fd, &msg);
                test(recv_output != -1, "Rcv Msg of %lu", i);
                if (recv_output <= 0) {
                    if (recv_output == 0) {
                        printf("Client disconnected: fd %d\n", fds[i].fd);
                    } else {
                        perror("recv");
                    }
                    close(fds[i].fd);
                    vec_remove(fds, i);
                    continue;
                }
                fppf(stdout, "Msg of %lu :%a\n", i, &msg_pp, &msg);

                // Respond to Message
                if (msg.to >= vec_len(fds)) {
                    fprintf(stderr, "Message to %d but only % connections\n",
                            msg.to, vec_len(fds));
                    continue;
                }
                // TODO: Check that msg.from is correct
                int nbytes_send = msg_send(fds[msg.to].fd, &msg);
                test(nbytes_send != -1, "Send Message");
                if (nbytes_send == -1) {
                    perror("Send");
                }
            }
        }
    }

    /// Close all connection
    for (u64 i = 0; i < vec_len(fds); i++) {
        test(close(fds[i].fd) == 0, "Close Connection N°%d", i);
    }
    return 0;
}
