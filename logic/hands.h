#ifndef HANDS_H
#define HANDS_H
#include "hand.h"
#include "player.h"
#include "tiles.h"

// Hands are all the hands of the fours players.
// This can be drawn
typedef struct Hands Hands;

Hands *hands_empty(void);
void hands_draw_from(Hands *hands, Tiles *from);
Hand *hands_get(Hands *hands, Player player);
void hands_free(Hands *hands);

#endif
