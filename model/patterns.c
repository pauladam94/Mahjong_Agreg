#include "../utils/better_int.h"
#include "pattern.h"
#include <stdio.h>
#include <stdlib.h>

void patterns_pp(FILE *file, const vec(Pattern *) patterns) {
    for (u64 i = 0; i < vec_len(patterns); i++) {
        fprintf(file, "Pat %lu :", i);
        pattern_pp(file, patterns[i]);
        if (i != vec_len(patterns) - 1) {
            fprintf(file, "\n");
        }
    }
}

void patterns_add_first_group_pattern(vec(Pattern *) patterns, Pattern *pat) {
    // FIRST SEQUENCE
    Tile *fst = NULL;
    Tile *snd = NULL;
    Tile *thrd = NULL;
    pattern_next_sequence(pat, &fst, &snd, &thrd);
    if (fst != NULL && snd != NULL && thrd != NULL &&
        !pattern_has_four_group(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_group(new_pattern, fst, snd, thrd);
        pattern_remove_tile(new_pattern, fst);
        pattern_remove_tile(new_pattern, snd);
        pattern_remove_tile(new_pattern, thrd);
        vec_push(patterns, new_pattern);
    }
    // FIRST THREE OF A KIND
    fst = NULL;
    snd = NULL;
    thrd = NULL;
    pattern_next_three_same(pat, &fst, &snd, &thrd);
    if (fst != NULL && snd != NULL && thrd != NULL &&
        !pattern_has_four_group(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_group(new_pattern, fst, snd, thrd);
        pattern_remove_tile(new_pattern, fst);
        pattern_remove_tile(new_pattern, snd);
        pattern_remove_tile(new_pattern, thrd);
        vec_push(patterns, new_pattern);
    }
    // FIRST PAIR
    fst = NULL;
    snd = NULL;
    pattern_next_pair(pat, &fst, &snd);
    if (fst != NULL && snd != NULL && !pattern_has_pair(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_pair(new_pattern, fst, snd);
        pattern_remove_tile(new_pattern, fst);
        pattern_remove_tile(new_pattern, snd);
        vec_push(patterns, new_pattern);
    }
    pattern_free(pat);
    /*
    Tile *t = pattern_get_tile(pat, 0);
    if (t != NULL) {
        pattern_remove_tile(pat, t);
        patterns_add_pattern(patterns, pat);
    } else {
        pattern_free(pat);
    }
    */
}

void patterns_free(vec(Pattern *) patterns) {
    for (u64 i = 0; i < vec_len(patterns); i++) {
        pattern_free(patterns[i]);
        patterns[i] = NULL;
    }
    vec_free(patterns);
}
