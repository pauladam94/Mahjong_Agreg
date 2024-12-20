#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Lipeikou]\n");
    reset();

    //is
    Hand *h = hand_from_string("222333444666s66z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(ryuuiisou(pat) == 13, "222333444666s66z is ryuuiisou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("222333789p666s66z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ryuuiisou(pat) == 0, "222333789p666s66z is not ryuuiisou");

    patterns_free(&patterns);
    hand_free(h);
}