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
    Hand *h = hand_from_string("123789m111p11789s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(junchan(pat) == 3, "123789m111p11789s is junchan");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("123789m111p22789s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(junchan(pat) == 0, "123789m111p22789s is not junchan");

    patterns_free(&patterns);
    hand_free(h);
}