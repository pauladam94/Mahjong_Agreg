#include "../utils/better_int.h"
#include "../utils/error.h"
#include "../utils/vec.h"
#include <stdio.h>

int main() {
    purple();
    printf("[Test Vec8]\n");
    reset();

    vec(int) v = NULL;
    for (int i = 0; i < 10; i++) {
        vec_push(v, i);
    }
    for (int i = 0; i < 10; i ++)
        vec_pop(v);

    test(vec_len(v) == 0, "10 Push 10 pop, len of 0");
    test(v == NULL, "10 Push 10 pop, vector is NULL");
    vec_free(v);
}
