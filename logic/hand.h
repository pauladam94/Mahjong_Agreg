#ifndef HAND_H
#define HAND_H

#include "tile.h"
#include <stdbool.h>

typedef struct Hand Hand;

bool is_yaku(Hand hand);

Hand *empty_hand(void);

void add_tile(Hand *hand, Tile *tile);

Tile get_tile(Hand *hand, int pos);

int get_hand_size(const Hand *hand);

Hand* hand_from_string(void);

void free_hand(Hand hand);

#endif // HAND_H
