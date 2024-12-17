#include "pattern.h"
#include "../utils/better_int.h"
#include "../utils/error.h"
#include "../utils/vec.h"
#include "tile.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Pattern {
    vec(vec(Tile *)) group;
    vec(GroupType) group_type;
    vec(Tile *) tiles; // The Pattern is partial until tiles is not empty
} Pattern;

Pattern *pattern_empty(void) {
    Pattern *pattern = calloc(sizeof(*pattern), 1);
    return pattern;
}

Pattern *pattern_from_tiles(vec(Tile *) tiles) {
    Pattern *pat = pattern_empty();
    pat->tiles = tiles;
    return pat;
}

void pattern_remove_tile(Pattern *pat, Tile *t) {
    tiles_remove_equals(&pat->tiles, t);
}

bool pattern_is_open(const Pattern *const pat) {
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case SEQUENCE_OPEN:
        case FOUR_OPEN:
        case THREE_OPEN:
            return true;
        default:
            break;
        }
    }
    return false;
}

bool pattern_is_complete(const Pattern *pat) {
    int n_group = 0;
    int n_pair = 0;
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case PAIR_CLOSE:
            n_pair++;
            break;
        case THREE_CLOSE:
        case THREE_OPEN:
        case FOUR_CLOSE:
        case SEQUENCE_OPEN:
        case SEQUENCE_CLOSE:
        case FOUR_OPEN:
            n_group++;
            break;
        }
    }
    return (n_pair == 1 && n_group == 4);
}

void pattern_add_group(Pattern *pat, vec(Tile *) group, GroupType type) {
    vec_push(pat->group, group);
    vec_push(pat->group_type, type);
}

void pattern_pp(FILE *file, const Pattern *pat) {
    fprintf(file, "|");
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        for (u64 j = 0; j < vec_len(pat->group[i]); j++) {
            tile_pp(file, pat->group[i][j]);
            if (j != vec_len(pat->group[i]) - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "|");
    }

    fprintf(file, " ");
    if (pat->tiles != NULL)
        tiles_pp(file, pat->tiles);
}

bool pattern_has_pair(Pattern *pat) {
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case PAIR_CLOSE:
            return true;
        default:
            break;
        }
    }
    return false;
}
bool pattern_has_four_group(Pattern *pat) {
    int n_group = 0;
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case SEQUENCE_CLOSE:
        case SEQUENCE_OPEN:
        case THREE_CLOSE:
        case THREE_OPEN:
            n_group++;
        default:
            break;
        }
        return false;
    }
    return n_group == 4;
}

Tile *pattern_get_tile(const Pattern *pat, u64 pos) {
    if (pos >= vec_len(pat->tiles)) {
        return NULL;
    }
    return pat->tiles[pos];
}

void pattern_free(Pattern *pat) {
    vec_free(pat->tiles);
    vec_free(pat->group_type);
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        vec_free(pat->group[i]);
    }
    vec_free(pat->group);
    free(pat);
}

void pattern_check(const Pattern *pat) {
    test(vec_len(pat->group) == vec_len(pat->group_type),
         "same size group group_type");
}

Pattern *pattern_copy(const Pattern *pat) {
    // pattern_check(pat);
    Pattern *res = pattern_empty();
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        vec_push(res->group, NULL);
        for (u64 j = 0; j < vec_len(pat->group[i]); j++) {
            vec_push(res->group[i], pat->group[i][j]);
        }
        vec_push(res->group_type, pat->group_type[i]);
    }
    res->tiles = tiles_copy(pat->tiles);
    return res;
}

vec(Tile *) pattern_next_pair(const Pattern *pat) {
    int i = 0;
    vec(Tile *) pair = NULL;

    while (true) {
        vec_push(pair, pattern_get_tile(pat, i));
        if (pair[vec_len(pair) - 1] == NULL) {
            vec_pop(pair);
            break;
        }
        if (vec_len(pair) >= 2 &&
            !tile_equals(pair[vec_len(pair) - 2], pair[vec_len(pair) - 1])) {
            vec_pop(pair);
        }
        if (vec_len(pair) == 2) {
            break;
        }
        i++;
    }
    if (vec_len(pair) != 2) {
        vec_free(pair);
    }
    return pair;
}

vec(Tile *) pattern_next_three_same(const Pattern *pat) {
    int i = 0;
    vec(Tile *) three = NULL;
    while (true) {
        vec_push(three, pattern_get_tile(pat, i));
        // End of pattern
        if (three[vec_len(three) - 1] == NULL) {
            vec_pop(three);
            break;
        }
        if (vec_len(three) >= 2 && !tile_equals(three[vec_len(three) - 2],
                                                three[vec_len(three) - 1])) {
            vec_pop(three);
        }
        // Complete the three
        if (vec_len(three) == 3) {
            break;
        }
        i++;
    }
    if (vec_len(three) != 3) {
        vec_free(three);
    }
    return three;
}

vec(Tile *) pattern_next_sequence(const Pattern *pat) {
    int i = 0;
    vec(Tile *) sequence = NULL;
    while (true) {
        vec_push(sequence, pattern_get_tile(pat, i));
        // End of pattern
        if (sequence[vec_len(sequence) - 1] == NULL) {
            vec_pop(sequence);
            break;
        }
        if (vec_len(sequence) > 1 &&
            !tile_adjacent(sequence[vec_len(sequence) - 2],
                           sequence[vec_len(sequence) - 1])) {
            vec_pop(sequence);
        }
        // Complete the sequence
        if (vec_len(sequence) == 3) {
            break;
        }
        i++;
    }
    if (vec_len(sequence) != 3) {
        vec_free(sequence);
    }
    return sequence;
}

vec(vec(Tile *)) pattern_without_pair(Pattern *pat) {
    vec(vec(Tile *)) pat_no_pair = NULL;
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case PAIR_CLOSE:
            break;
        default:
            vec_push(pat_no_pair, pat->group[i]);
            break;
        }
    }
    return pat_no_pair;
}

vec(vec(Tile *)) pattern_get_group(Pattern *pat) { return pat->group; }

vec(GroupType) pattern_get_group_type(Pattern *pat) { return pat->group_type; }

vec(GroupType) pattern_get_group_type_without_pair(Pattern *pat) {
    vec(GroupType) gt_no_pair = NULL;
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case PAIR_CLOSE:
            break;
        default:
            vec_push(gt_no_pair, pat->group_type[i]);
            break;
        }
    }
    return gt_no_pair;
}
