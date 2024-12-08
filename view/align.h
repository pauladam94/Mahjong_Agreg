#ifndef ALIGN_H
#define ALIGN_H

typedef enum Align { LEFT, RIGHT, UP, DOWN } Align;

float align_rotation(Align align);
void align_pos_hand(Align align, int* x, int*y, int posX, int posY, int i);
void align_pos_discard(Align align, int *x, int *y, int posX, int posY, int i);

#endif // ALIGN_H
