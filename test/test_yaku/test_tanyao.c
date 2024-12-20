#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Tanyao]\n");
    reset();

    //is
    Hand *h = hand_from_string("222456777m222p88s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(tanyao(pat) == 1, "222456777m222p88s is tanyao");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111456777m222p88s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(tanyao(pat) == 0, "111456777m222p88s is not tanyao");

    patterns_free(&patterns);
    hand_free(h);
}