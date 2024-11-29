#include "tile.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    switch (t.tile) {}
}
bool is_wind(Tile t) {}
bool is_family(Tile t) { return !is_honor(t); }

bool is_adjacent(Tile t0, Tile t1) {
    if (!(is_family(t0) || is_family(t1))) {
        return false;
    }
    switch (t0.tile) {
    case M1:
        printf("test");
        break;
    }
};
