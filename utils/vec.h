#ifndef VEC_H
#define VEC_H

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/// Header data for a light-weight implelentation of typed vecs.
typedef struct vec_header {
    uint64_t cap;
    uint64_t len;
} vec_header;

void vec_maybe_expand(void **vec, uint64_t size, uint64_t new_size);
void vec_maybe_shrink(void **vec, uint64_t size, uint64_t new_size);

#define vec(T) T *

#define vec_get_header(V) (((vec_header *)(V)) - 1)

#define vec_len(V) ((V) ? vec_get_header(V)->len : 0)

#define suppress_warning_sizeof_begin  \
#pragma clang diagnostic push \\
#pragma clang diagnostic ignored "-Wfloat-equal -Wdeprecated" \\

#define suppress_warning_sizeof_end #pragma clang diagnostic pop

// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wfloat-equal -Wdeprecated"
// #pragma clang diagnostic pop
// suppress_warning_sizeof_begin
// suppress_warning_sizeof_end                                      
#define vec_push(V, E)                                                         \
    do {                                                                       \
        vec_maybe_expand((void **)&(V), (uint64_t)sizeof(*(V)),                \
                         vec_len(V) + 1);                                      \
        (V)[vec_len(V)] = E;                                                   \
        vec_get_header(V)->len++;                                              \
    } while (0)

#define vec_remove(V, I)                                                       \
    do {                                                                       \
        if (I < 0 || I >= vec_len(V)) {                                        \
            fprintf(stderr,                                                    \
                    "Invalid remove at position %" PRIu64                      \
                    " in vec of size %" PRIu64 "\n",                           \
                    I, vec_len(V));                                            \
            exit(1);                                                           \
        }                                                                      \
        memmove(V + I, V + I + 1, sizeof(V) * (vec_len(V) - I - 1));           \
        vec_get_header(V)->len--;                                              \
                                                                               \
    } while (0)

#define vec_pop(V)                                                             \
    do {                                                                       \
        if (vec_get_header(V)->size != 0)                                      \
            vec_get_header(V)->size--;                                         \
    } while (0)

#define vec_free(V)                                                            \
    do {                                                                       \
        if (V) {                                                               \
            memset(V, 0, (uint64_t)vec_len(V) * (sizeof *(V)));                \
            free(vec_get_header(V));                                           \
            (V) = NULL;                                                        \
        }                                                                      \
    } while (0)
#define vec_free_all(V, F)                                                     \
    do {                                                                       \
        if (V) {                                                               \
            for (uint64_t vec_index = 0; vec_index < vec_len(V); vec_index++)  \
                F((V)[vec_index]);                                             \
            memset(V, 0, (uint64_t)vec_len(V) * (sizeof *(V)));                \
            free(vec_get_header(V));                                           \
            (V) = NULL;                                                        \
        }                                                                      \
    } while (0)

#endif // VEC_H
