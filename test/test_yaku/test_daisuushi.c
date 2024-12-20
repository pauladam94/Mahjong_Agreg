#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Daisuushi]\n");
    reset();

    //is
    Hand *h = hand_from_string("11m111222333444z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(daisuushi(pat) == 13, "11m111222333444z is daisuushi");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("11m111222333s444z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(daisuushi(pat) == 0, "11m111222333s444z is not daisuushi");

    patterns_free(&patterns);
    hand_free(h);
}