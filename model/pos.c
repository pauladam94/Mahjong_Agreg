#include "raylib.h"
#include "pos.h"
#include <stdlib.h>

const float SPEED = 0.01;

typedef struct Pos {
    Vector2 begin;
    Vector2 end;
    float t;
} Pos;

Vector2 pos_get(Pos *pos) {
    Vector2 res;
    float t = pos->t;
    float v = -2 * t + 2;
    float x = t < 0.5 ? 4 * t * t * t : 1 - v * v * v / 2;
    res.x = pos->begin.x * (1. - x) + x * pos->end.x;
    res.y = pos->begin.y * (1. - x) + x * pos->end.y;
    return res;
}

void pos_update(Pos *pos) {
    if (pos->t >= 1.) {
        pos->t = 1.;
    } else if (pos->t < 0.) {
        pos->t = 0.;
    } else {
        pos->t += SPEED;
    }
}

Pos *pos_from_vec(Vector2 vec) {
    Pos *res = calloc(sizeof(*res), 1);
    res->begin = vec;
    res->end = vec;
    res->t = 1.;
    return res;
}

Pos *pos_transi(Vector2 begin, Vector2 end) {
    Pos *res = calloc(sizeof(*res), 1);
    res->begin = begin;
    res->end = end;
    res->t = 0.1;
    return res;
}

void pos_free(Pos* pos) {
    free(pos);
}
