#include "settings.h"
#include "raylib.h"
#include <stdlib.h>

void settings_resize(Settings *settings) {
    settings->tile_height = settings->height / 12;
    settings->tile_width = settings->tile_height * 0.7;
    settings->thickness = (float)settings->tile_height / 20;
    settings->roundness = 0.02;
}

Settings settings_init(int width, int height) {
    Settings res;
    res.width = width;
    res.height = height;
    settings_resize(&res);
    return res;
}

void settings_zoom(Settings *settings) {
    settings->width *= 0.9;
    settings->height *= 0.9;
    settings_resize(settings);
}
void settings_unzoom(Settings *settings) {
    settings->width *= 1.1;
    settings->height *= 1.1;
    settings_resize(settings);
}

void settings_apply(Settings settings) {
    SetWindowSize(settings.width, settings.height);
}
