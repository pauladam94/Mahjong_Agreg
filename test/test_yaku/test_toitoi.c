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
    Hand *h = hand_from_string("111222m333444s55z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(toitoi(pat) == 2, "111222m333444s55z is toitoi");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111456m333444s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(toitoi(pat) == 0, "111456m333444s55z is not toitoi");

    patterns_free(&patterns);
    hand_free(h);
}