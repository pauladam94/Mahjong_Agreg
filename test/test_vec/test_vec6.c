#include "../../utils/error.h"
#include "../../utils/vec.h"
#include "assert.h"
#include <stdio.h>

int main() {
    purple();
    printf("[Test Vec6]\n");
    reset();

    vec(int) v = NULL;
    vec_free(v);
}
