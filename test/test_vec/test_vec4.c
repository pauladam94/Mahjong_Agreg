#include "../../utils/better_int.h"
#include "../../utils/error.h"
#include "../../utils/vec.h"
#include "assert.h"
#include <stdio.h>

int main() {
    purple();
    printf("[Test Vec4]\n");
    reset();
    u64 len = 0;

    vec(int) v = NULL;

    for (u64 i = 0; i < 10000; i++) {
        vec_push(v, i);
        len++;
        assert(vec_len(v) == len);
    }
    for (u64 i = 0; i < 100; i++) {
        if (i % 2 == 0) {
            vec_remove(v, i * 10);
        } else {
            vec_pop(v);
        }
        len--;
        assert(vec_len(v) == len);
    }
    test(true, "Test of length through push / remove operation");
    vec_free(v);
}
