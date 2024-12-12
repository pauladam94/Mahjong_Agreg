#include "vec.h"
#include "better_int.h"

void vec_maybe_expand(void **vec, u64 size, u64 min_size) {
    if (min_size <= 0)
        return;

    vec_header *header = vec_get_header(*vec);
    if (!*vec) {
        uint64_t initial_capacity = 32;
        void *new_data = malloc((sizeof *header) + (initial_capacity * size));
        header = (vec_header *)new_data;

        header->cap = initial_capacity;
        header->len = 0;

    } else if (min_size > header->cap) {
        while (min_size > header->cap)
            header->cap *= 2;
        header = (vec_header *)realloc(header,
                                       (sizeof *header) + (header->cap * size));
    }
    *vec = (void *)(header + 1);
}
