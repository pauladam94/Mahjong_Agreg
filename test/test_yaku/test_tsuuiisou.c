#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Tsuuiisou]\n");
    reset();

    //is
    Hand *h = hand_from_string("11122233344455z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(tsuuiisou(pat) == 13, "11122233344455z is tsuuiisou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111222333444s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(tsuuiisou(pat) == 0, "111222333444s55z is not tsuuiisou");

    patterns_free(&patterns);
    hand_free(h);
}