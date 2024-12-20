#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Shousuushi]\n");
    reset();

    //is
    Hand *h = hand_from_string("111m11122233344z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(shousuushi(pat) == 13, "111m11122233344z is shousuushi");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111m111222333s44z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(shousuushi(pat) == 0, "111m111222333s44z is not shousuushi");

    patterns_free(&patterns);
    hand_free(h);
}