#include "event.h"
#include "../model/tile.h"

Event event_pick(Tile *tile) {
    Event event;
    event.type = PICK;
    event.pick.tile = tile;
    return event;
}
