#include "hand.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Hands {
    Hand *hands[4];
} Hands;

Hands *hands_empty(void) {
    Hands *res = calloc(sizeof(*res), 1);
    for (Player i = Player0; i <= Player3; i++) {
        res->hands[i] = hand_empty();
    }
    return res;
}

void hands_draw_from(Hands *hands, Tiles *from) {
    for (int i = 0; i < 4; i++) {
        free(hands->hands[i]);
        hands->hands[i] = hand_draw_from(from, 13);
        hand_sort(hands->hands[i]);
    }
}

Hand *hands_get(Hands *hands, Player player) { return hands->hands[player]; }

void hands_free(Hands *hands) {
    for (int i = 0; i < 4; i++) {
        hand_free(hands->hands[i]);
    }
    free(hands);
}
