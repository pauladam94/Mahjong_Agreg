#include "../logic/hand.h"
#include "../logic/tile.h"
#include "../logic/tiles.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("=====[TEST Hand]=====\n");
    reset();
    Hand *h1 = hand_from_string("123m2p3s1m3z");
    Hand *h2 = hand_from_string("123m234p333345s222z");
    test("1123m2p3s3z is not complete", !hand_is_complete(h1));
    test("123m234p333345s222z is complete", hand_is_complete(h2));
}
