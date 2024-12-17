#include "patterns.h"
#include "../utils/better_int.h"
#include "pattern.h"
#include <stdio.h>
#include <stdlib.h>

void patterns_pp(FILE *file, vec(Pattern *) const patterns) {
    for (u64 i = 0; i < vec_len(patterns); i++) {
        fprintf(file, "Pat %lu :", i);
        pattern_pp(file, patterns[i]);
        if (i != vec_len(patterns) - 1) {
            fprintf(file, "\n");
        }
    }
}

vec(Pattern *) patterns_first_group_pattern(Pattern *pat) {
    vec(Pattern *) res = NULL;
    vec(Tile *) group;
    // FIRST SEQUENCE
    group = pattern_next_sequence(pat);
    if (group != NULL && !pattern_has_four_group(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_group(new_pattern, group, SEQUENCE_CLOSE);
        for (u64 i = 0; i < vec_len(group); i++) {
            pattern_remove_tile(new_pattern, group[i]);
        }
        vec_push(res, new_pattern);
    } else {
        vec_free(group);
    }
    // FIRST THREE OF A KIND
    group = pattern_next_three_same(pat);
    if (group != NULL && !pattern_has_four_group(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_group(new_pattern, group, THREE_CLOSE);
        for (u64 i = 0; i < vec_len(group); i++) {
            pattern_remove_tile(new_pattern, group[i]);
        }
        vec_push(res, new_pattern);
    } else {
        vec_free(group);
    }
    // FIRST PAIR
    group = pattern_next_pair(pat);
    if (group != NULL && !pattern_has_pair(pat)) {
        Pattern *new_pattern = pattern_copy(pat);
        pattern_add_group(new_pattern, group, PAIR_CLOSE);
        for (u64 i = 0; i < vec_len(group); i++) {
            pattern_remove_tile(new_pattern, group[i]);
        }
        vec_push(res, new_pattern);
    } else {
        vec_free(group);
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
    return res;
}

void patterns_free(vec(Pattern *) * patterns) {
    for (u64 i = 0; i < vec_len(*patterns); i++) {
        pattern_free((*patterns)[i]);
        (*patterns)[i] = NULL;
    }
    vec_free(*patterns);
}
