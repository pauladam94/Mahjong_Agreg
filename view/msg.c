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
    vec_push(buff, 0); // 0
    vec_push(buff, 0); // 1
    vec_push(buff, 0); // 2
    vec_push(buff, 0); // 3

    vec_push(buff, (u8)msg.from); // 4
    vec_push(buff, (u8)msg.to);   // 5
    vec_push(buff, (u8)msg.type); // 6

    switch (msg.type) {
    case SET_PLAYER_NUMBER:
        vec_push(buff, (u8)msg.set_player_number.player);
        break;
    default:
        printf("TODO other type");
        break;
    }

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
    switch (msg.type) {
    case SET_PLAYER_NUMBER:
        msg.set_player_number.player = buff[7];
        break;
    default:
        printf("TODO other type");
        break;
    }
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

void msg_type_pp(FILE *file, MsgType msg_type) {
    switch (msg_type) {
    case SET_PLAYER_NUMBER:
        fprintf(file, "SET_PLAYER_NUMBER");
        break;
    case CHAT:
        fprintf(file, "CHAT");
        break;
    case EVENT:
        fprintf(file, "Event");
        break;
    }
}

void msg_pp(FILE *file, Msg *msg) {
    fppf(file, "{from : %d ; to %d ; type: %a}", msg->from, msg->to,
         msg_type_pp, msg->type);
}
