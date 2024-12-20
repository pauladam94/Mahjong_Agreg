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
    Hand *h = hand_from_string("789789m123123p33s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(ryanpeikou(pat) == 3, "789789m123123p33s is ryanpeikou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("789123m123123p33s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ryanpeikou(pat) == 0, "789123m123123p33s is not ryanpeikou");

    patterns_free(&patterns);
    hand_free(h);
}