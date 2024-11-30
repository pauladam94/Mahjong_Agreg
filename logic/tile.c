#include "tile.h"
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
    Z1, // West Wind
    Z2, // East Wind
    Z3, // North Wind
    Z4, // South Wind
    Z5, // White Dragon
    Z6, // Red Dragon
    Z7  // Green Dragon
} _Tile;

typedef struct Tile {
    _Tile tile;
} Tile;

int get_number(Tile t) {
    switch (t.tile) {
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

bool is_honor(Tile t) {
    switch (t.tile) {
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

bool is_dragon(Tile t) {
    switch (t.tile) {
    case Z5:
    case Z6:
    case Z7:
        return true;
    default:
        return false;
    }
}

bool is_wind(Tile t) {
    switch (t.tile) {
    case Z1:
    case Z2:
    case Z3:
    case Z4:
        return true;
    default:
        return false;
    }
}

bool is_family(Tile t) { return !is_honor(t); }

bool is_adjacent(Tile t0, Tile t1) {
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
    _Tile res;
    switch (name[1]) {
    case 'm':
        res = M1 + (int)name[0] - 1;
        break;
    case 'p':
        res = P1 + (int)name[0] - 1;
        break;
    case 's':
        res = S1 + (int)name[0] - 1;
        break;
    case 'z':
        res = Z1 + (int)name[0] - 1;
        break;
    }
    Tile *t = malloc(sizeof(*t));
    t->tile = res;
    return t;
}

static Image *tiles_image;
static bool loaded_has_been_done = false;

void load_all_tiles() {
    loaded_has_been_done = true;
    tiles_image = malloc(sizeof(*tiles_image) * Z7);
    tiles_image[M1] = LoadImage("data/B1.png");
    tiles_image[M2] = LoadImage("data/B2.png");
    tiles_image[M3] = LoadImage("data/B3.png");
    tiles_image[M4] = LoadImage("data/B4.png");
    tiles_image[M5] = LoadImage("data/B5.png");
    tiles_image[M6] = LoadImage("data/B6.png");
    tiles_image[M7] = LoadImage("data/B7.png");
    tiles_image[M8] = LoadImage("data/B8.png");
    tiles_image[M9] = LoadImage("data/B9.png");
}

Image tile_image(const Tile *tile) {
    if (!loaded_has_been_done) {
        load_all_tiles();
    }
    return tiles_image[tile->tile];
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