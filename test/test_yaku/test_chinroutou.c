#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Chinroutou]\n");
    reset();

    //is
    Hand *h = hand_from_string("111999m111p11999s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(chinroutou(pat) == 13, "111999m111p11999s is chinroutou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111999m111p22999s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(chinroutou(pat) == 0, "111999m111p22999s is not chinroutou");

    patterns_free(&patterns);
    hand_free(h);
}