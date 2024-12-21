#include "../../model/hand.h"
#include "../../model/yaku.h"
#include "../../model/patterns.h"
#include "../../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Yakus]\n");
    reset();

    //is
    Hand *h = hand_from_string("23423466677788m");

    vec(Yaku) yakus = find_max_yaku(h);

    test(vec_len(yakus) == 3, "found 3 yakus in 23423466677788m");
    for (u64 i = 0; i < vec_len(yakus); i++) {
        printf("%s for %d Han\n", yaku_name[yakus[i].id], yakus[i].han);
    }

    hand_free(h);
    vec_free(yakus);
}