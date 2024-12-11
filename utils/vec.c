#include "vec.h"
#include "better_int.h"

void vec_maybe_expand(void **vec, uint64_t size, uint64_t min_size) {
    if (min_size <= 0)
        return;

    vec_header *header = vec_get_header(*vec);
    if (!*vec) {
        uint64_t initial_capacity = 32;
        void *new_data =
            malloc((sizeof *header) + (uint64_t)(initial_capacity * size));
        header = (vec_header *)new_data;

        header->cap = initial_capacity;
        header->len = 0;

    } else if (min_size > header->cap) {
        while (min_size > header->cap)
            header->cap *= 2;
        header = (vec_header *)realloc(
            header, (sizeof *header) + (uint64_t)(header->cap * size));
    }
    *vec = (void *)(header + 1);
}
