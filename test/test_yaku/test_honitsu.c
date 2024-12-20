#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Honitsu]\n");
    reset();

    //is
    Hand *h = hand_from_string("111222444555m11z");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(honitsu(pat) == 3, "111222444555m11z is honitsu");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111456p333444m11z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[0];
    test(honitsu(pat) == 0, "111456p333444m11z is not honitsu");

    patterns_free(&patterns);
    hand_free(h);
}