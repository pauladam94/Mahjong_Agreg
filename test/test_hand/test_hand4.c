#include "../../model/hand.h"
#include "../../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 4]\n");
    Hand* h = hand_from_string("1m2p7s3z");
    hand_free(h);
    reset();
}
