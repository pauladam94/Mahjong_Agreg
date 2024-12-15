#ifndef MESSAGE_H
#define MESSAGE_H
#include "../model/player.h"
#include "../model/tile.h"
#include "../utils/better_int.h"
#include "../utils/vec.h"

// Msg is an structure that is easily manipulable
// It's purpose is that every communication should pass through messages :
// - to simplify what the server does
// - to simplify what the client have to send and receive.
typedef struct Msg {
    Player from;
    Player to;
    enum { SetPlayerNumber, RawData, Chat } type;
    union {
        struct {
            Tile *tile;
        } chi;
        struct {
            vec(char) raw_data;
        } chat;
    };
} Msg;

// Same API as `send` but write in a Message buffer
// This functions free the message send
int msg_send(int fd, Msg *msg);
// Same API as `recv` but write the received message inside of `msg` argument
int msg_recv(int fd, Msg *msg);

int msg_size(Msg msg);

Msg msg_from_buffer(char *buff, u64 len);

void msg_free(Msg msg);

void msg_pp(FILE *file, Msg *msg);

#endif // MESSAGE_H
