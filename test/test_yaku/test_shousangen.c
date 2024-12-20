#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Shousangen]\n");
    reset();

    //is
    Hand *h = hand_from_string("111m222p55566677z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(shousangen(pat) == 2, "111m222p55566677z is shousangen");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111m123p555666s77z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(shousangen(pat) == 0, "111m123p555666s77z is not shousangen");

    patterns_free(&patterns);
    hand_free(h);
}