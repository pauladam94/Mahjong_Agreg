#ifndef MESSAGE_H
#define MESSAGE_H
#include "../model/player.h"
#include "../model/tile.h"
#include "../utils/better_int.h"
#include "../utils/vec.h"

typedef enum MsgType { SetPlayerNumber } MsgType;
typedef struct MsgData {
    union {
        Tile *tile;
        vec(char) raw_data;
    };
} MsgData;

typedef struct Msg {
    Player from;
    Player to;
    MsgType msg_type;
    MsgData data;
} Msg;

void msg_send(Msg msg);
Msg msg_recv();

Msg msg_from_buffer(char *buff, u64 len);

void msg_pp(FILE *file, Msg msg);

#endif // MESSAGE_H
