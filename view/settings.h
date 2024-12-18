#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct Settings {
    int width;
    int height;
    int tile_height;
    int tile_width;
    float thickness;
    float roundness;
} Settings;

Settings settings_init(int width, int height);
void settings_zoom(Settings *setings);
void settings_unzoom(Settings *settings);
void settings_apply(Settings settings);

#endif // SETTINGS_H
