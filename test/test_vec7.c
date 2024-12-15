#include "../utils/better_int.h"
#include "../utils/error.h"
#include "../utils/vec.h"
#include <assert.h>
#include <stdio.h>

vec(int) all_pair(vec(int) v) {
    vec(int) pair = NULL;
    for (u64 i = 0; i < vec_len(v); i++) {
        if (v[i] % 2 == 0) {
            vec_push(pair, v[i]);
        }
    }
    return pair;
}

int main() {
    purple();
    printf("[Test Vec7]\n");
    reset();

    vec(int) v = NULL;

    for (int i = 0; i < 1000; i++) {
        vec_push(v, i);
    }
    vec(int) pair = all_pair(v);
    for (u64 i = 0; i < vec_len(pair); i++) {
        assert(pair[i] % 2 == 0);
    }

    test(true, "v = 1000 insert all pairs of v");
    test(vec_len(pair) == 500, "only 500 elements in pair");
    vec_free(v);
    vec_free(pair);
    test(v == NULL, "v is NULL after free");
}
