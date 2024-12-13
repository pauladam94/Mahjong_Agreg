#include "../model/hand.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 7]\n");
    reset();
    Hand *h = hand_from_string("1111123123123m234p");
    test(!hand_is_complete(h), "1111123123123m234p is complete");

    hand_free(h);
}
