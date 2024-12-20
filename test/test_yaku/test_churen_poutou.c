#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Churen Poutou]\n");
    reset();

    //is
    Hand *h = hand_from_string("11123456789991m");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(churen_poutou(pat) == 13, "11123456789991m is churen_poutou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("222333789p666s66z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(churen_poutou(pat) == 0, "222333789p666s66z is not churen_poutou");

    patterns_free(&patterns);
    hand_free(h);
}