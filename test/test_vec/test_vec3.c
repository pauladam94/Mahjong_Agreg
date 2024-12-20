#include "../../utils/better_int.h"
#include "../../utils/error.h"
#include "../../utils/vec.h"
#include <stdio.h>

int main() {
    purple();
    printf("[Test Vec2]\n");
    reset();

    vec(int) v = NULL;

    for (int i = 0; i < 1000; i++) {
        vec_push(v, i);
    }
    for (u64 i = 0; i < 10; i++) {
        vec_remove(v, i * 10);
    }
    test(vec_len(v) == 990, "1000 insert 10 remove : vec_len(v) == 990");
    vec_free(v);
    test(v == NULL, "v is NULL after free");
}
