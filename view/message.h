#ifndef MESSAGE_H
#define MESSAGE_H

#include "../model/player.h"

typedef struct Message Message;

void send(Player to);
void recv(Player to);

#endif // MESSAGE_H
