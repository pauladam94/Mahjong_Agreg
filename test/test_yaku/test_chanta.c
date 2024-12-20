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
    Hand *h = hand_from_string("123789m111p11z777z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(chanta(pat) == 2, "123789m111p11z777z is chanta");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("123789m111p22s777z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(chanta(pat) == 0, "123789m111p22s777z is not chanta");

    patterns_free(&patterns);
    hand_free(h);
}