#ifndef POS_H
#define POS_H
#include "raylib.h"
typedef struct Pos Pos;

void pos_update(Pos* pos);
Vector2 pos_get(Pos* pos);
Pos* pos_from_vec(Vector2 vec);
Pos* pos_transi(Vector2 begin, Vector2 end);
void pos_free(Pos* pos);

#endif // POS_H
