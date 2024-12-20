#include "../utils/vec.h"
#include "../utils/error.h"
#include "../utils/better_int.h"
#include <stdio.h>

int main() {
    purple();
    printf("[Test Vec1]\n");
    reset();

    vec(int) v = NULL;

    for (int i = 0; i < 100; i ++) {
        vec_push(v, i);
    }
    for (u64 i = 0; i < 10; i ++) {
        vec_remove(v, i);
    }
    test(vec_len(v) == 90, "0..99 insert 0..9 remove gives size of 90");
    test(v[0] == 1, "0..99 insert 0..9 remove, v[0] == 1");
    test(v[1] == 3, "0..99 insert 0..9 remove, v[1] == 3");
    test(v[2] == 5, "0..99 insert 0..9 remove, v[2] == 5");
    test(v[3] == 7, "0..99 insert 0..9 remove, v[3] == 7");
    vec_free(v);
}
