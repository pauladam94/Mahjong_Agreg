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
    Hand *h = hand_from_string("111m111p11123455s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(sanshoku_doukou(pat) == 2, "111m111p11123455s is sanshoku_doukou");

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("111m123p11123455s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(sanshoku_doukou(pat) == 0, "111m123p11123455s is not sanshoku_doukou");

    patterns_free(&patterns);
    hand_free(h);
}