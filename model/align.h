#ifndef ALIGN_H
#define ALIGN_H
#include "../view/settings.h"
#include "raylib.h"

typedef enum Align { LEFT, RIGHT, UP, DOWN } Align;

float align_rotation(Align align);
Vector2 align_pos_hand(Align align, int posX, int posY, int i,
                       Settings settings);
Vector2 align_pos_discard(Align align, int posX, int posY, int i,
                          Settings settings);
Rectangle align_rect(Align align, Vector2 pos, Settings settings);

#endif // ALIGN_H
