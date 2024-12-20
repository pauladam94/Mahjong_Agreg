#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Suuankou]\n");
    reset();

    //is
    Hand *h = hand_from_string("111222888444s55z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(suuankou(pat) == 13, "111222888444s55z is suuankou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111222789m444s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(suuankou(pat) == 0, "111222789m444s55z is not suuankou");

    patterns_free(&patterns);
    hand_free(h);
}