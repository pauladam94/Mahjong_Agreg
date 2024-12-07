#ifndef BUTTON_H
#define BUTTON_H
#include "align.h"
#include <stdbool.h>

bool button_is_pressed(int posX, int posY, int width, int height, Align align);

bool button_text_is_pressed(int posX, int posY, int width, int height,
                            const char *text, Align align);
#endif // BUTTON_H
