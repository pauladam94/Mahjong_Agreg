#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Itttsuu]\n");
    reset();

    //is
    Hand *h = hand_from_string("123456789m111p99s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(ittsuu(pat) == 2, "123456789m111p99s is ittsuu");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("123456777m111p99s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ittsuu(pat) == 0, "123456777m111p99s is not ittsuu");

    patterns_free(&patterns);
    hand_free(h);
}