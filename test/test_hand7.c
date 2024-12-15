#include "../model/hand.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 7]\n");
    reset();
    Hand *h = hand_from_string("111p");
    test(!hand_is_complete(h), "111p is not complete");

    hand_free(h);
}
