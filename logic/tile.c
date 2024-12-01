#include "tile.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    M1, // Man 1
    M2, // ...
    M3,
    M4,
    M5,
    M6,
    M7,
    M8,
    M9,
    P1, // Pin 1
    P2, // ...
    P3,
    P4,
    P5,
    P6,
    P7,
    P8,
    P9,
    S1, // Su 1
    S2, // ...
    S3,
    S4,
    S5,
    S6,
    S7,
    S8,
    S9,
    Z1, // East Wind
    Z2, // South Wind
    Z3, // West Wind
    Z4, // North Wind
    Z5, // White Dragon
    Z6, // Green Dragon
    Z7  // Red Dragon
} _Tile;

typedef struct Tile {
    _Tile tile;
} Tile;

int get_number(Tile *t) {
    switch (t->tile) {
    case M1:
    case P1:
    case S1:
        return 1;
    case M2:
    case P2:
    case S2:
        return 2;
    case M3:
    case P3:
    case S3:
        return 3;
    case M4:
    case P4:
    case S4:
        return 4;
    case M5:
    case P5:
    case S5:
        return 5;
    case M6:
    case P6:
    case S6:
        return 6;
    case M7:
    case P7:
    case S7:
        return 7;
    case M8:
    case P8:
    case S8:
        return 8;
    case M9:
    case P9:
    case S9:
        return 9;
    case Z1:
    case Z2:
    case Z3:
    case Z4:
    case Z5:
    case Z6:
    case Z7:
        return -1;
    }
}

bool is_honor(Tile *t) {
    switch (t->tile) {
    case Z1:
    case Z2:
    case Z3:
    case Z4:
    case Z5:
    case Z6:
    case Z7:
        return true;
    default:
        return false;
    }
}

bool is_dragon(Tile *t) {
    switch (t->tile) {
    case Z5:
    case Z6:
    case Z7:
        return true;
    default:
        return false;
    }
}

bool is_wind(Tile *t) {
    switch (t->tile) {
    case Z1:
    case Z2:
    case Z3:
    case Z4:
        return true;
    default:
        return false;
    }
}

bool is_family(Tile *t) { return !is_honor(t); }

bool is_adjacent(Tile *t0, Tile *t1) {
    if (!(is_family(t0) || is_family(t1))) {
        return false;
    }
    int n0 = get_number(t0);
    int n1 = get_number(t1);
    return (n0 == n1 + 1) || (n0 + 1 == n1);
};

// 1m for Man number 1
// 1s for Su, 1p for Pin
// then 1z to 7z for winds and dragons
Tile *tile_from_string(const char *name) {
    if (strlen(name) != 2) {
        fprintf(stderr,
                "Error : %s not describe a tile. Do 1m or 4s or 2z instead.\n",
                name);
        exit(1);
    }
    Tile *t = calloc(sizeof(*t), 1);
    _Tile res;
    printf("IN tile_from_string : %c %c\n", name[0], name[1]);
    switch (name[1]) {
    case 'm':
        res = M1 + ((int)name[0] - '0') - 1;
        break;
    case 'p':
        res = P1 + ((int)name[0] - '0') - 1;
        break;
    case 's':
        res = S1 + ((int)name[0] - '0') - 1;
        break;
    case 'z':
        res = Z1 + ((int)name[0] - '0') - 1;
        break;
    }
    t->tile = res;
    return t;
}

static Texture2D *tiles_textures;
static bool loaded_has_been_done = false;

void load_all_tiles() {
    loaded_has_been_done = true;
    tiles_textures = calloc(sizeof(*tiles_textures), Z7 + 1);
    tiles_textures[M1] = LoadTexture("data/C1.png");
    tiles_textures[M2] = LoadTexture("data/C2.png");
    tiles_textures[M3] = LoadTexture("data/C3.png");
    tiles_textures[M4] = LoadTexture("data/C4.png");
    tiles_textures[M5] = LoadTexture("data/C5.png");
    tiles_textures[M6] = LoadTexture("data/C6.png");
    tiles_textures[M7] = LoadTexture("data/C7.png");
    tiles_textures[M8] = LoadTexture("data/C8.png");
    tiles_textures[M9] = LoadTexture("data/C9.png");
    tiles_textures[P1] = LoadTexture("data/R1.png");
    tiles_textures[P2] = LoadTexture("data/R2.png");
    tiles_textures[P3] = LoadTexture("data/R3.png");
    tiles_textures[P4] = LoadTexture("data/R4.png");
    tiles_textures[P5] = LoadTexture("data/R5.png");
    tiles_textures[P6] = LoadTexture("data/R6.png");
    tiles_textures[P7] = LoadTexture("data/R7.png");
    tiles_textures[P8] = LoadTexture("data/R8.png");
    tiles_textures[P9] = LoadTexture("data/R9.png");
    tiles_textures[S1] = LoadTexture("data/B1.png");
    tiles_textures[S2] = LoadTexture("data/B2.png");
    tiles_textures[S3] = LoadTexture("data/B3.png");
    tiles_textures[S4] = LoadTexture("data/B4.png");
    tiles_textures[S5] = LoadTexture("data/B5.png");
    tiles_textures[S6] = LoadTexture("data/B6.png");
    tiles_textures[S7] = LoadTexture("data/B7.png");
    tiles_textures[S8] = LoadTexture("data/B8.png");
    tiles_textures[S9] = LoadTexture("data/B9.png");
    tiles_textures[Z1] = LoadTexture("data/VE.png");
    tiles_textures[Z2] = LoadTexture("data/VS.png");
    tiles_textures[Z3] = LoadTexture("data/VO.png");
    tiles_textures[Z4] = LoadTexture("data/VN.png");
    tiles_textures[Z5] = LoadTexture("data/DB.png");
    tiles_textures[Z6] = LoadTexture("data/DV.png");
    tiles_textures[Z7] = LoadTexture("data/DR.png");
}

Texture2D tile_texture(const Tile *tile) {
    if (!loaded_has_been_done) {
        load_all_tiles();
    }
    return tiles_textures[tile->tile];
}

void free_tiles_textures() {
    for (size_t i = 0; i < Z7; i++) {
        UnloadTexture(tiles_textures[i]);
    }
    free(tiles_textures);
}

void pp_tile(FILE *file, Tile *t) {
    switch (t->tile) {
    case M1:
        fprintf(file, "1m");
        break;
    case P1:
        fprintf(file, "1p");
        break;
    case S1:
        fprintf(file, "1s");
        break;
    case M2:
        fprintf(file, "2m");
        break;
    case P2:
        fprintf(file, "2p");
        break;
    case S2:
        fprintf(file, "2s");
        break;
    case M3:
        fprintf(file, "3p");
        break;
    case P3:
        fprintf(file, "3p");
        break;
    case S3:
        fprintf(file, "3s");
        break;
    case M4:
        fprintf(file, "4m");
        break;
    case P4:
        fprintf(file, "4p");
        break;
    case S4:
        fprintf(file, "4s");
        break;
    case M5:
        fprintf(file, "5m");
        break;
    case P5:
        fprintf(file, "5p");
        break;
    case S5:
        fprintf(file, "5s");
        break;
    case M6:
        fprintf(file, "6m");
        break;
    case P6:
        fprintf(file, "6p");
        break;
    case S6:
        fprintf(file, "6s");
        break;
    case M7:
        fprintf(file, "7m");
        break;
    case P7:
        fprintf(file, "7p");
        break;
    case S7:
        fprintf(file, "7s");
        break;
    case M8:
        fprintf(file, "8m");
        break;
    case P8:
        fprintf(file, "8p");
        break;
    case S8:
        fprintf(file, "8s");
        break;
    case M9:
        fprintf(file, "9m");
        break;
    case P9:
        fprintf(file, "9p");
        break;
    case S9:
        fprintf(file, "9s");
        break;
    case Z1:
        fprintf(file, "1z");
        break;
    case Z2:
        fprintf(file, "2z");
        break;
    case Z3:
        fprintf(file, "3z");
        break;
    case Z4:
        fprintf(file, "4z");
        break;
    case Z5:
        fprintf(file, "5z");
        break;
    case Z6:
        fprintf(file, "6z");
        break;
    case Z7:
        fprintf(file, "7z");
        break;
    }
}

void free_tile(Tile *tile) { free(tile); }
bool tiles_equals(Tile *t1, Tile *t2) { return t1->tile == t2->tile; }

Tile *next_dora(const Tile *tile) {
    printf("tile = %d\n", tile->tile);
    Tile *new_tile = calloc(sizeof(*new_tile), 1);
    _Tile res;
    switch (tile->tile) {
    case M1:
    case P1:
    case S1:
    case M2:
    case P2:
    case S2:
    case M3:
    case P3:
    case S3:
    case M4:
    case P4:
    case S4:
    case M5:
    case P5:
    case S5:
    case M6:
    case P6:
    case S6:
    case M7:
    case P7:
    case S7:
    case M8:
    case P8:
    case S8:
    case Z1:
    case Z2:
    case Z3:
    case Z5:
    case Z6:
        res = tile->tile + 1;
        break;
    case M9:
    case P9:
    case S9:
        res = tile->tile - 8;
        break;
    case Z4:
        res = tile->tile - 3;
        break;
    case Z7:
        res = tile->tile - 2;
        break;
    }
    new_tile->tile = res;
    return new_tile;
}
