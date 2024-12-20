#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Shanshoku Doujun]\n");
    reset();

    //is
    Hand *h = hand_from_string("123m123p12355566s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(shanshoku_doujun(pat) == 2, "123m123p12355566s is shanshoku_doujun");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("123m234p12355566s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(shanshoku_doujun(pat) == 0, "123m234p12355566s is not shanshoku_doujun");

    patterns_free(&patterns);
    hand_free(h);
}