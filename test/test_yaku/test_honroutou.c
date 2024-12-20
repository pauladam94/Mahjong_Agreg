#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Honroutou]\n");
    reset();

    //is
    Hand *h = hand_from_string("111999m111p999s11z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(honroutou(pat) == 2, "111999m111p999s11z is honroutou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111999m111p888s11z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(honroutou(pat) == 0, "111999m111p888s11z is not honroutou");

    patterns_free(&patterns);
    hand_free(h);
}