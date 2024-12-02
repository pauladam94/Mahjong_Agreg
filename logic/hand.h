#ifndef HAND_H
#define HAND_H

#include <stdbool.h>

typedef struct Hand Hand;

// 4 sequences or three same tile and 1 pair
bool hand_is_complete(const Hand *hand);
// complete with a yaku (or yaku that are enough alone)
bool hand_is_valid(const Hand *hand);
// Hand is complete without any terminal or honor
bool hand_is_all_simple(const Hand *hand);

void hand_add_tile(Hand *hand);
void hand_remove_tile(Hand *hand);
Hand *hand_from_string(const char *s);

void hand_free(Hand *hand);

bool tiles_is_opened(const Hand *hand);
bool tiles_is_closed(const Hand *hand);

#endif // HAND_H
