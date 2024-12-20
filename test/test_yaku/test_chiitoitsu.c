#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Chiitoitsu]\n");
    reset();

    //is
    Hand *h = hand_from_string("113355m4455p6677s");
    vec(Pattern *) patterns = hand_patterns(h);
    test(vec_len(patterns) >= 1, "Can detect 7 pairs");

    if (vec_len(patterns) >= 1) {
        Pattern *pat = patterns[0];
        test(chiitoitsu(pat) == 2, "113355m4455p6677s is chiitoitsu");
    }

    patterns_free(&patterns);
    hand_free(h);

    //is not
    h = hand_from_string("123456789m111p22s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[0];
    test(chiitoitsu(pat) == 0, "123456789m111p22s is not chiitoitsu");

    patterns_free(&patterns);
    hand_free(h);
}