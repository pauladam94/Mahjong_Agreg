#ifndef HANDS_H
#define HANDS_H
#include "../view/context.h"
#include "hand.h"
#include "player.h"
#include "../utils/vec.h"


// Hands are all the hands of the fours players.
// This can be drawn
typedef struct Hands Hands;

Hands *hands_empty(void);
void hands_pick_from(Hands *hands, vec(Tile *)from);
Hand *hands_get(Hands *hands, Player player);
void hands_free(Hands *hands);
void hands_draw(Hands *hands);
void hands_update(Hands *hands, vec(Tile *)tiles, Context ctx);

#endif // HANDS_H
