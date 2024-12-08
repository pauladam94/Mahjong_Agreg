#include "stdlib.h"
#include "tile.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
typedef struct Tiles {
    int len;
    int cap;
    Tile **arr;
} Tiles;

Tiles *tiles_empty() {
    Tiles *tiles = calloc(sizeof(*tiles), 1);
    return tiles;
}

void tiles_pp(FILE *file, const Tiles *tiles) {
    for (int i = 0; i < tiles->len; i++) {
        tile_pp(file, tiles->arr[i]);
        if (i != tiles->len - 1) {
            printf(" ");
        }
    }
}

int comp(const void *a, const void *b) {
    const Tile *t1 = *(const Tile **)a;
    const Tile *t2 = *(const Tile **)b;
    return tile_comp(t1, t2);
}

void tiles_sort(Tiles *tiles) {
    qsort(tiles->arr, tiles->len, sizeof(tiles->arr), &comp);
}

void tiles_add(Tiles *tiles, const Tile *tile) {
    tiles->len++;
    if (tiles->len > tiles->cap) {
        tiles->cap = (tiles->cap == 0) ? 1 : tiles->cap * 2;
        tiles->arr = realloc(tiles->arr, sizeof(tiles->arr) * tiles->cap);
    }
    tiles->arr[tiles->len - 1] = (Tile *)tile;
}

Tile *tiles_get(const Tiles *tiles, int pos) {
    if (pos < 0 || pos >= tiles->len) {
        return NULL;
    }
    return tiles->arr[pos];
}

void tiles_remove(Tiles *tiles, int pos) {
    if (tiles->len == 0) {
        fprintf(stderr, "Removing Tile in Empty Tiles\n");
        exit(1);
    }
    tile_free(tiles->arr[pos]);
    memmove(tiles->arr + pos, tiles->arr + pos + 1,
            sizeof(tiles->arr) * (tiles->len - pos - 1));
    tiles->len--;
}

int tiles_size(const Tiles *tiles) { return tiles->len; }

Tiles *tiles_from_string(const char *s) {
    Tiles *tiles = tiles_empty();
    char tile_string[3] = {0};
    tile_string[2] = '\0';
    int len = 0;
    int cap = 0;
    char *buf = NULL;

    for (int i = 0; i < (int)strlen(s); i++) {
        char c = s[i];
        // if we treat a digit
        if (isdigit(c)) {
            len++;
            if (len > cap) {
                cap = cap == 0 ? 1 : cap * 2;
                buf = realloc(buf, cap);
            }
            buf[len - 1] = c;
        } else {
            for (int j = 0; j < len; j++) {
                tile_string[0] = buf[j];
                tile_string[1] = c;
                Tile *tile = tile_from_string(tile_string);
                tiles_add(tiles, tile);
            }
            free(buf);
            buf = NULL;
            len = 0;
            cap = 0;
        }
    }
    if (buf != NULL) {
        fprintf(stderr, "%s Not the right format of tiles", s);
        exit(1);
    }
    free(buf);
    return tiles;
}

Tiles *tiles_all(void) {
    return tiles_from_string(
        "111122223333444455556666777788889999m111122223333"
        "444455556666777788889999p11112222333344445555666677"
        "7788889999s111122223333444455556667777z");
}

Tile *tiles_random_from(const Tiles *from) {
    return tiles_get(from, rand() % (from->len));
}

void tiles_free(Tiles *tiles) {
    for (int i = 0; i < tiles->len; i++) {
        tile_free(tiles->arr[i]);
    }
    free(tiles->arr);
    free(tiles);
}

Tiles *tiles_copy(const Tiles *tiles) {
    Tiles *res = tiles_empty();
    for (int i = 0; i < tiles_size(tiles); i++) {
        tiles_add(res, tiles_get(tiles, i));
    }
    return res;
}

void tiles_remove_equals(Tiles *tiles, Tile *tile) {
    for (int i = 0; i < tiles_size(tiles); i++) {
        if (tile_equals(tile, tiles_get(tiles, i))) {
            tiles_remove(tiles, i);
            break;
        }
    }
}

Tile *tiles_pick_from(Tiles *from) {
    Tile *t = tiles_random_from(from);
    tiles_remove_equals(from, t);
    return t;
}
