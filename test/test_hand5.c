#include "../model/hand.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 5]\n");
    Hand* h = hand_empty();
    hand_free(h);
    reset();
}
