#include "../model/hand.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 6]\n");
    reset();
    Hand *h1 = hand_from_string("123m2p3s1m3z");
    Hand *h2 = hand_from_string("11111123m2p3s1m3z");
    test("1123m2p3s3z is not complete", !hand_is_complete(h1));
    test("11111123m2p3s1m3z is not complete", !hand_is_complete(h2));

    hand_free(h1);
    hand_free(h2);
}
