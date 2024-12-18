#ifndef HANDS_H
#define HANDS_H
#include "../utils/vec.h"
#include "../view/context.h"
#include "../view/settings.h"
#include "hand.h"
#include "player.h"

// Hands are all the hands of the fours players.
// This can be drawn
typedef struct Hands Hands;

Hands *hands_empty(Settings settings);
void hands_pick_from(Hands *hands, vec(Tile *) * from, Settings settings);
Hand *hands_get(Hands *hands, Player player);
void hands_free(Hands *hands);
void hands_draw(Hands *hands, Settings settings);
void hands_update(Hands *hands, vec(Tile *) * tiles, Context ctx,
                  Settings settings);

#endif // HANDS_H
