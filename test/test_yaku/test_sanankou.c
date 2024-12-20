#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Sanankou]\n");
    reset();

    //is
    Hand *h = hand_from_string("123m222333555s55z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(sanankou(pat) == 2, "123m222333555s55z is sanankou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("123m123333p555s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(sanankou(pat) == 0, "123m123333p555s55z is not sanankou");

    patterns_free(&patterns);
    hand_free(h);
}