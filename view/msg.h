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

// void send(Player to);
// void recv(Player to);

#endif // MESSAGE_H
