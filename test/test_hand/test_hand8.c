#include "../../model/hand.h"
#include "../../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 8]\n");
    reset();
    Hand *h = hand_from_string("1p");
    test(!hand_is_complete(h), "1p is not complete");

    hand_free(h);
}
