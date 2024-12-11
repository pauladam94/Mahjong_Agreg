#include "../utils/vec.h"
#include "stdlib.h"
#include "tile.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void tiles_pp(FILE *file, const vec(Tile *) tiles) {
    for (uint64_t i = 0; i < vec_len(tiles); i++) {
        tile_pp(file, tiles[i]);
        if (i != vec_len(tiles) - 1) {
            printf(" ");
        }
    }
}

void tiles_sort(vec(Tile *) tiles) {
    qsort(tiles, vec_len(tiles), sizeof(tiles), &tile_comp);
}

vec(Tile *) tiles_from_string(const char *s) {
    vec(Tile *) tiles = NULL;
    char tile_string[3] = {0};
    tile_string[2] = '\0';
    vec(char) buf = NULL;

    for (int i = 0; i < (int)strlen(s); i++) {
        char c = s[i];
        // if we treat a digit
        if (isdigit(c)) {
            vec_push(buf, c);
        } else {
            for (uint64_t j = 0; j < vec_len(buf); j++) {
                tile_string[0] = buf[j];
                tile_string[1] = c;
                Tile *tile = tile_from_string(tile_string);
                vec_push(tiles, tile);
            }
            vec_free(buf);
        }
    }
    vec_free(buf);
    if (buf != NULL) {
        fprintf(stderr, "%s Not the right format of tiles", s);
        exit(1);
    }
    free(buf);
    return tiles;
}

vec(Tile *) tiles_all(void) {
    return tiles_from_string(
        "111122223333444455556666777788889999m111122223333"
        "444455556666777788889999p11112222333344445555666677"
        "7788889999s111122223333444455556667777z");
}

Tile *tiles_random_from(vec(Tile *) from) {
    return from[rand() % (vec_len(from))];
}

vec(Tile *) tiles_copy(const vec(Tile *) tiles) {
    vec(Tile *) res = NULL;
    for (uint64_t i = 0; i < vec_len(tiles); i++) {
        vec_push(res, tiles[i]);
    }
    return res;
}

int tiles_remove_equals(vec(Tile *) tiles, Tile *tile) {
    for (uint64_t i = 0; i < vec_len(tiles); i++) {
        if (tile_equals(tile, tiles[i])) {
            vec_remove(tiles, i);
            return i;
        }
    }
    return -1;
}

Tile *tiles_pick_from(vec(Tile *) from) {
    Tile *t = tiles_random_from(from);
    tiles_remove_equals(from, t);
    return t;
}
