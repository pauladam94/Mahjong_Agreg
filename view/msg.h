#ifndef MESSAGE_H
#define MESSAGE_H
#include "../model/player.h"
#include "../model/tile.h"

typedef enum MsgType { SetPlayerNumber } MsgType;
typedef struct MsgData {
    Tile *tile;
} MsgData;

typedef struct Msg {
    Player from;
    Player to;
    MsgType msg_type;
    MsgData data;
} Msg;

void msg_send(Player to);
void msg_recv(Player to);

void msg_pp(FILE *file, Msg msg);

#endif // MESSAGE_H
