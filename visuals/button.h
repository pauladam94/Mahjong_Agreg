#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

bool button_is_pressed(int posX, int posY, int width, int height);
bool button_text_is_pressed(int posX, int posY, int width, int height,
                            const char *text);

#endif // BUTTON_H
