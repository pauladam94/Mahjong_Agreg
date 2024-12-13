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
    tiles_remove_equals(pat->tiles, t);
}

bool pattern_is_open(Pattern *pat) {
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case PON:
        case KAHN:
        case CHI:
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
        case PAIR:
            n_pair++;
            break;
        case SEQUENCE:
        case THREE_OF_KIND:
        case FOUR_OF_KIND:
        case PON:
        case KAHN:
        case CHI:
            n_group++;
            break;
        }
    }
    return (n_pair == 1 && n_group == 4);
}

void pattern_add_group(Pattern *pat, Tile *t0, Tile *t1, Tile *t2,
                       GroupType type) {
    vec(Tile *) group = NULL;
    vec_push(group, t0);
    vec_push(group, t1);
    vec_push(group, t2);
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
        case PAIR:
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
        case SEQUENCE:
        case THREE_OF_KIND:
        case PON:
        case CHI:
            n_group++;
        default:
            break;
        }
        return false;
    }
    return n_group == 4;
}

void pattern_add_pair(Pattern *pat, Tile *t0, Tile *t1) {
    if (!pattern_has_pair(pat)) {
        vec(Tile *) pair = NULL;
        vec_push(pair, t0);
        vec_push(pair, t1);
        vec_push(pat->group, pair);
        vec_push(pat->group_type, PAIR);
    } else {
        fprintf(stderr, "Add pair when Pattern has a pair\n");
    }
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
    res->tiles = tiles_copy((const vec(Tile *))pat->tiles);
    return res;
}

void pattern_next_pair(const Pattern *pat, Tile **fst, Tile **snd) {
    int i = 0;
    Tile *tile = NULL;
    while (true) {
        tile = pattern_get_tile(pat, i);
        if (tile == NULL) {
            return;
        }
        if (*fst == NULL) {
            *fst = tile;
        } else if (*snd == NULL) {
            if (tile_equals(*fst, tile)) {
                *snd = tile;
                break;
            }
        }
        i++;
    }
}
void pattern_next_three_same(const Pattern *pat, Tile **fst, Tile **snd,
                             Tile **thrd) {
    int i = 0;
    Tile *tile = NULL;
    while (true) {
        tile = pattern_get_tile(pat, i);
        if (tile == NULL) {
            return;
        }
        if (*fst == NULL) {
            *fst = tile;
        } else if (*snd == NULL) {
            if (tile_equals(*fst, tile)) {
                *snd = tile;
            }
        } else if (*thrd == NULL) {
            if (tile_equals(*snd, tile)) {
                *thrd = tile;
                break;
            }
        }
        i++;
    }
}
void pattern_next_sequence(const Pattern *pat, Tile **fst, Tile **snd,
                           Tile **thrd) {
    int i = 0;
    Tile *tile = NULL;
    while (true) {
        tile = pattern_get_tile(pat, i);
        if (tile == NULL) {
            return;
        }
        if (*fst == NULL) {
            *fst = tile;
        } else if (*snd == NULL) {
            if (tile_adjacent(*fst, tile)) {
                *snd = tile;
            }
        } else if (*thrd == NULL) {
            if (tile_adjacent(*snd, tile)) {
                *thrd = tile;
                break;
            }
        }
        i++;
    }
}

vec(vec(Tile *)) pattern_without_pair(Pattern *pat) {
    vec(vec(Tile *)) pat_no_pair = NULL;
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case PAIR:
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
