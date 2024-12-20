#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Daisangen]\n");
    reset();

    //is
    Hand *h = hand_from_string("111m22p555666777z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(daisangen(pat) == 13, "111m222p55566677z is daisangen");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111m22p555666s777z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(daisangen(pat) == 0, "111m222p555666s77z is not daisangen");

    patterns_free(&patterns);
    hand_free(h);
}