#include "stdlib.h"
#include "tile.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef struct Tiles {
    int len;
    int cap;
    Tile **arr;
    bool opened;
} Tiles;

Tiles *empty_tiles() {
    Tiles *tiles = calloc(sizeof(*tiles), 1);
    return tiles;
}

void tiles_add_tile(Tiles *tiles, Tile *tile) {
    tiles->len++;
    if (tiles->len > tiles->cap) {
        tiles->cap = (tiles->cap == 0) ? 1 : tiles->cap * 2;
        tiles->arr = realloc(tiles->arr, sizeof(tiles->arr) * tiles->cap);
    }
    tiles->arr[tiles->len - 1] = tile;
}

Tile *get_tile(const Tiles *tiles, int pos) { return tiles->arr[pos]; }

void tiles_remove_tile(Tiles *tiles, int pos) {
    if (tiles->len == 0) {
        fprintf(stderr, "Removing Tile in Empty Tiles\n");
        exit(1);
    }
    memmove(tiles->arr + pos, tiles->arr + pos + 1,
            sizeof(tiles->arr) * (tiles->len - pos - 1));
    tiles->len--;
}

int tiles_size(const Tiles *tiles) { return tiles->len; }

Tiles *tiles_from_string(const char *s) {
    Tiles *tiles = empty_tiles();
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
                tiles_add_tile(tiles, tile);
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
    return tiles;
}

void tiles_free(Tiles *tiles) {
    for (int i = 0; i < tiles->len; i++) {
        free(tiles->arr[i]);
    }
    free(tiles->arr);
    free(tiles);
}

bool is_opened(const Tiles *tiles) { return tiles->opened; }
bool is_closed(const Tiles *tiles) { return !tiles->opened; }
