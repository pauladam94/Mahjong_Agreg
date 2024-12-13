#include "../utils/better_int.h"
#include "../utils/vec.h"
#include "tile.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum GroupType {
    // Closed
    Pair,
    Sequence,    // Is NOT a Chi
    ThreeOfKind, // IS NOT Pon
    FourOfKind,  // IS NOT Kahn
    // Open
    Pon,
    Kahn,
    Chi,
} GroupType;

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
        case Pon:
        case Kahn:
        case Chi:
            return true;
        default:
            break;
        }
    }
    return false;
}

bool pattern_is_complete(Pattern *pat) {
    int n_group = 0;
    int n_pair = 0;
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case Pair:
            n_pair++;
            break;
        case Sequence:
        case ThreeOfKind:
        case FourOfKind:
        case Pon:
        case Kahn:
        case Chi:
            n_group++;
            break;
        }
    }
    return (n_pair == 1 && n_group == 4);
}

void pattern_add_group(Pattern *pat, Tile *t0, Tile *t1, Tile *t2) {
    for (int i = 0; i < 4; i++) {
        if (pat->group[0][i] != NULL) {
            if (i == 3) {
                fprintf(stderr, "Add a group when Pattern has 3 group\n");
                return;
            }
            continue;
        }
        pat->group[0][i] = t0;
        pat->group[1][i] = t1;
        pat->group[2][i] = t2;
        break;
    }
}

void pattern_pp(FILE *file, const Pattern *pat) {
    fprintf(file, "|");
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (pat->group[i][j] != NULL) {
                tile_pp(file, pat->group[i][j]);
                if (i != 2)
                    fprintf(file, " ");
            }
        }
        fprintf(file, "|");
    }
    fprintf(file, "|");
    fprintf(file, " ");
    if (pat->tiles != NULL)
        tiles_pp(file, (const vec(Tile *))pat->tiles);
}

bool pattern_has_pair(Pattern *pat) {
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case Pair:
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
        case Sequence:
        case ThreeOfKind:
        case Pon:
        case Chi:
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
    free(pat);
}

Pattern *pattern_copy(const Pattern *pat) {
    Pattern *res = pattern_empty();
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            res->group[i][j] = pat->group[i][j];
        }
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
        case Pair:
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

vec(GroupType *) pattern_get_group_type_without_pair(Pattern *pat) {
    vec(GroupType *) gt_no_pair = NULL;
    for (u64 i = 0; i < vec_len(pat->group); i++) {
        switch (pat->group_type[i]) {
        case Pair:
            break;
        default:
            vec_push(gt_no_pair, &pat->group_type[i]);
            break;
        }
    }
    return gt_no_pair;
}