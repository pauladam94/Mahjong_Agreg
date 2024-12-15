#ifndef VEC_H
#define VEC_H

#include "better_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Header data for a light-weight implelentation of typed vecs.
typedef struct vec_header {
    u64 cap;
    u64 len;
} vec_header;

#define vec(T) T *

#define vec_get_header(V) (((vec_header *)(V)) - 1)

#define vec_len(V) ((V == NULL) ? 0 : vec_get_header(V)->len)

// Prapre the vector for having one more element
#define vec_prepare_push_one(V)                                                \
    do {                                                                       \
        if ((V) == NULL) {                                                     \
            (V) = (void *)((vec_header *)calloc(                               \
                               sizeof(vec_header) + sizeof(*(V)), 1) +         \
                           1);                                                 \
            vec_get_header(V)->cap = 1;                                        \
        } else {                                                               \
            if (vec_len(V) + 1 > vec_get_header(V)->cap) {                     \
                vec_get_header(V)->cap = vec_get_header(V)->cap == 0           \
                                             ? 1                               \
                                             : vec_get_header(V)->cap * 2;     \
                (V) =                                                          \
                    (void *)((vec_header *)realloc(                            \
                                 vec_get_header(V),                            \
                                 sizeof(vec_header) +                          \
                                     vec_get_header(V)->cap * sizeof(*(V))) +  \
                             1);                                               \
            }                                                                  \
        }                                                                      \
    } while (0)

#define vec_decrease_len(V)                                                    \
    do {                                                                       \
        if (V != NULL) {                                                       \
            vec_get_header(V)->len--;                                          \
        }                                                                      \
        if (vec_get_header(V)->len == 0) V = NULL;                             \
    } while (0) 

#define vec_push(V, E)                                                         \
    do {                                                                       \
        vec_prepare_push_one(V);                                               \
        vec_get_header(V)->len++;                                              \
        (V)[vec_len(V) - 1] = E;                                               \
    } while (0)

#define vec_remove(V, I)                                                       \
    do {                                                                       \
        if (I >= vec_len(V) || vec_len(V) == 0) {                              \
            fprintf(stderr,                                                    \
                    "Invalid remove at position %lu in vec of size %lu\n", I,  \
                    vec_len(V));                                               \
            exit(1);                                                           \
        }                                                                      \
        memmove(V + I, V + I + 1, sizeof(*(V)) * (vec_len(V) - I - 1));        \
        vec_decrease_len(V);                                                   \
    } while (0)

#define vec_pop(V)                                                             \
    do {                                                                       \
        if (vec_get_header(V)->len == 0) {                                     \
            fprintf(stderr, "Pop on empty vector\n");                          \
            exit(1);                                                           \
        }                                                                      \
        vec_decrease_len(V);                                                   \
    } while (0)

#define vec_free(V)                                                            \
    do {                                                                       \
        if (V != NULL) {                                                       \
            memset(V, 0, (u64)vec_len(V) * (sizeof *(V)));                     \
            free(vec_get_header(V));                                           \
            (V) = NULL;                                                        \
        }                                                                      \
    } while (0)


#define vec_free_all(V, F)                                                     \
    do {                                                                       \
        if (V) {                                                               \
            for (u64 vec_index = 0; vec_index < vec_len(V); vec_index++)       \
                F((V)[vec_index]);                                             \
            memset(V, 0, (u64)vec_len(V) * (sizeof *(V)));                     \
            free(vec_get_header(V));                                           \
            (V) = NULL;                                                        \
        }                                                                      \
    } while (0)

#endif // VEC_H
