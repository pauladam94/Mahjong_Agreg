#ifndef EVENT_H
#define EVENT_H

#include "tile.h"
#include "wind.h"

typedef struct Event {
    enum {
        CHI,       // Somebody do a CHI
        PON,       // Somebody do a PON
        KAHN_OPEN, // Somebody KAHN the tile of somebody else
        DISCARD,   // Somebody Discard a tile
        PICK,      // Somebody pick a tile
        TSUMO,     // Somebody do a tsumo after
        RON,       // Somebody do a ron after somebody has discard
    } type;
    union {
        struct {
            Tile *fst; // Tile of the chi with lowest number
        } chi;
        struct {
            Wind wind; // Player Wind that does the pon
        } pon;
        struct {
            Wind wind; // Player Wind that does the pon
        } kahn_open;
        struct {
        } kahn_discard;
        struct {
            Tile *tile;
        } pick;
        struct {
        } kahn;
        struct {
            Wind wind;
            Tile *tile;
        } discard;
    };
} Event;

Event event_pick(Tile *tile);

#endif // EVENT_H
