#include "tile.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Pattern {
    Tile *group[3][4]; // The four sequences or three of a kind
    Tile *pair[2];
    Tiles *tiles; // The Pattern is partial until tiles is not NULL
} Pattern;

Pattern *pattern_empty(void) {
    Pattern *pattern = calloc(sizeof(*pattern), 1);
    return pattern;
}

Pattern *pattern_from_tiles(Tiles *tiles) {
    Pattern *pat = pattern_empty();
    pat->tiles = tiles;
    return pat;
}

void pattern_remove_tile(Pattern *pat, Tile *t) {
    for (int i = 0; i < tiles_size(pat->tiles); i++) {
        if (tile_equals(t, tiles_get(pat->tiles, i))) {
            tiles_remove(pat->tiles, i);
            break;
        }
    }
}

bool pattern_is_complete(Pattern *pat) {
    bool res = true;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            res = res && (pat->group[i][j] != NULL);
        }
    }
    res = res && (pat->pair[0] != NULL);
    res = res && (pat->pair[1] != NULL);
    return res;
}

void pattern_add_group(Pattern *pat, Tile *t0, Tile *t1, Tile *t2) {
    for (int i = 0; i < 4; i++) {
        if (pat->group[0][i] != NULL) {
            if (i == 3) {
                fprintf(stderr, "Add a group when Pattern has 3 group\n");
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
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (pat->group[i][j] != NULL) {
                tile_pp(file, pat->group[i][j]);
                fprintf(file, " ");
            }
        }
        fprintf(file, "|");
    }
    fprintf(file, " ");
    if (pat->tiles != NULL)
        tiles_pp(file, pat->tiles);
}

void pattern_add_pair(Pattern *pat, Tile *t0, Tile *t1) {
    if (pat->pair[0] == NULL) {
        pat->pair[0] = t0;
        pat->pair[1] = t1;
    } else {
        fprintf(stderr, "Add pair when Pattern has a pair\n");
    }
}

Tile *pattern_get_tile(Pattern *pat, int pos) {
    return tiles_get(pat->tiles, pos);
}

void pattern_free(Pattern *pat) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            tile_free(pat->group[i][j]);
        }
    }
    tile_free(pat->pair[0]);
    tile_free(pat->pair[1]);
    free(pat);
}

Pattern *pattern_copy(Pattern *pat) {
    Pattern *res = pattern_empty();
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            res->group[i][j] = tile_copy(pat->group[i][j]);
        }
    }
    res->pair[0] = tile_copy(pat->pair[0]);
    res->pair[1] = tile_copy(pat->pair[1]);

    res->tiles = tiles_copy(pat->tiles);
    return res;
}

void pattern_next_three_same(Pattern *pat, Tile **fst, Tile **snd,
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
void pattern_next_sequence(Pattern *pat, Tile **fst, Tile **snd, Tile **thrd) {
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
