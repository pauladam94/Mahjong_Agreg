#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Chinitsu]\n");
    reset();

    //is
    Hand *h = hand_from_string("11122244455777m");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(chinitsu(pat) == 6, "11122244455777m is chinitsu");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111222789p44455m");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(chinitsu(pat) == 0, "111222789p44455m is not chinitsu");

    patterns_free(&patterns);
    hand_free(h);
}