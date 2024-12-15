#include "../model/hand.h"
#include "../model/patterns.h"
#include "../model/yaku.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Yakus 1]\n");
    reset();

    Hand *h = hand_from_string("789789m111222p33s");
    vec(Pattern *) patterns = hand_patterns(h);

    test(vec_len(patterns) >= 1, "Almost one pattern from 789789m111222p33s");
    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(lipeikou(pat) == 1, "789789m111222p33ss is lipeikou");

    hand_free(h);
    patterns_free(&patterns);
}
