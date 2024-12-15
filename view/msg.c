#include "msg.h"
#include "../utils/pp.h"
#include "poll.h"
#include <netdb.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

vec(char) msg_to_bytes(Msg msg) {
    vec(char) buff = NULL;

    // Space for writing size of the message
    vec_push(buff, 0);
    vec_push(buff, 0);
    vec_push(buff, 0);
    vec_push(buff, 0);

    vec_push(buff, (u8)msg.from);
    vec_push(buff, (u8)msg.to);
    vec_push(buff, (u8)msg.type);

    vec(int) buff_int = (vec(int))buff;
    buff_int[0] = (u32)vec_len(buff);

    return buff;
}

Msg msg_from_bytes(vec(char) buff) {
    if (vec_len(buff) < 2) {
        fprintf(stderr, "Error buff too small for receiving message\n");
    }
    Msg msg = {0};
    msg.from = (char)buff[4];
    msg.to = (char)buff[5];
    msg.type = (char)buff[6];
    return msg;
}

int msg_recv(int fd, Msg *msg) {
    memset(msg, 0, sizeof(*msg));

    // Receive lenght of the message
    u32 nbytes_recv = 0;
    int res = recv(fd, &nbytes_recv, sizeof(nbytes_recv), MSG_PEEK);
    if (res <= 0) {
        return res;
    }

    vec(char) buff = NULL;
    for (u32 i = 0; i < nbytes_recv; i++) {
        vec_push(buff, 0);
    }
    nbytes_recv = recv(fd, buff, vec_len(buff), 0);
    *msg = msg_from_bytes(buff);
    return nbytes_recv;
}

int msg_send(int fd, Msg *msg) {
    vec(char) buff = msg_to_bytes(*msg);
    int nbytes_send = send(fd, buff, vec_len(buff), 0);
    vec_free(buff);
    return nbytes_send;
}

void msg_pp(FILE *file, Msg *msg) {
    fprintf(file, "{from : %d; to %d; type: %d}", msg->from, msg->to,
            msg->type);
}
