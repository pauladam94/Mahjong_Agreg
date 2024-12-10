#ifndef CONTEXT_H
#define CONTEXT_H
#include "raylib.h"
#include <stdbool.h>

typedef struct Context {
    Vector2 mouse;
    bool mouse_clicked;
} Context;

Context context_get();

#endif // CONTEXT_H
