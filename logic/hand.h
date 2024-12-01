#ifndef HAND_H
#define HAND_H

#include "tile.h"
#include <stdbool.h>

typedef struct Hand Hand;

Hand *empty_hand(void);
// 1m12p124s1z is the hand with Man 1, Pin 1, Pin 2, Su 1, Su 2, Su 4, West Wind
Hand *hand_from_string(const char *s);

Tile* get_tile(const Hand *hand, int pos);

int hand_size(const Hand *hand);
void free_hand(const Hand *hand);
void add_tile(Hand *hand, Tile *tile);
void remove_tile(Hand *hand, int pos);

bool is_yaku(const Hand *hand);
bool is_opened(const Hand *hand);
bool is_closed(const Hand *hand);
#endif // HAND_H
