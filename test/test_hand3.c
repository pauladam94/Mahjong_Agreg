#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 3]\n");
    Hand* h = hand_from_string("111m2345p7s23m123z");
    hand_free(h);
    reset();
}
