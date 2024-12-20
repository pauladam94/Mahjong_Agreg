#include "../../model/hand.h"
#include "../../model/player.h"
#include "../../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 5]\n");
    Hand* h = hand_empty(Player0);
    hand_free(h);
    reset();
}
