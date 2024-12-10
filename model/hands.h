#ifndef HANDS_H
#define HANDS_H
#include "../view/context.h"
#include "hand.h"
#include "player.h"
#include "tiles.h"

// Hands are all the hands of the fours players.
// This can be drawn
typedef struct Hands Hands;

Hands *hands_empty(void);
void hands_pick_from(Hands *hands, Tiles *from);
Hand *hands_get(Hands *hands, Player player);
void hands_free(Hands *hands);
void hands_draw(Hands *hands);
void hands_update(Hands *hands, Tiles* tiles, Context ctx);

#endif // HANDS_H
