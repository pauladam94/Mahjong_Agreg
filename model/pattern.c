#include "../utils/vec.h"
#include "tile.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Pattern {
    Tile *group[3][4]; // The four sequences or three of a kind
    Tile *pair[2];
    vec(Tile *) tiles; // The Pattern is partial until tiles is not NULL
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

bool pattern_is_complete(Pattern *pat) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (pat->group[i][j] == NULL)
                return false;
        }
    }
    if (pat->pair[0] == NULL)
        return false;
    if (pat->pair[1] == NULL)
        return false;
    return true;
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

void pattern_pp(FILE *file, Pattern *pat) {
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
    if (pat->pair[0] != NULL && pat->pair[1] != NULL) {
        tile_pp(file, pat->pair[0]);
        fprintf(file, " ");
        tile_pp(file, pat->pair[1]);
    }
    fprintf(file, "|");
    fprintf(file, " ");
    if (pat->tiles != NULL)
        tiles_pp(file, (const vec(Tile *))pat->tiles);
}

bool pattern_has_pair(Pattern *pat) {
    return pat->pair[0] != NULL && pat->pair[1] != NULL;
}
bool pattern_has_four_group(Pattern *pat) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (pat->group[i][j] == NULL)
                return false;
        }
    }
    return true;
}

void pattern_add_pair(Pattern *pat, Tile *t0, Tile *t1) {
    if (!pattern_has_pair(pat)) {
        pat->pair[0] = t0;
        pat->pair[1] = t1;
    } else {
        fprintf(stderr, "Add pair when Pattern has a pair\n");
    }
}

Tile *pattern_get_tile(const Pattern *pat, int pos) {
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
    res->pair[0] = pat->pair[0];
    res->pair[1] = pat->pair[1];

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

const Tile ***pattern_get_group(Pattern *pat) {
    printf("\npat->group[0][0] = %d\n", tile_number(pat->group[0][0]));
    return (Tile ***)(pat->group);
}

const Tile **pattern_get_pair(Pattern *pat) {
    return (Tile **)pat->pair;
}