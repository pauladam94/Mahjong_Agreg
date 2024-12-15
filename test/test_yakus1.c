#include "../model/hand.h"
#include "../utils/error.h"
#include "../model/yaku.h"

int main() {
    purple();
    printf("[TEST Yakus 1]\n");
    reset();

    const Hand *h = hand_from_string("789789m111222p33s");
    Pattern *pat = patterns_pop(hand_patterns(h));
    test("789789m111222p33ss is lipeikou", lipeikou(pat) == 1);
    free(h);
}
