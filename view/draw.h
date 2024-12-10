#ifndef DRAW_H
#define DRAW_H
#include "../model/align.h"
#include "../model/tile.h"

void reset_hover_pressed();
void tile_hover_set(Tile *tile);
void tile_pressed_set(Tile *tile);
void tile_draw(const Tile *tile, Vector2 pos, Align align);
void tiles_free_textures();

void highlight_tile_draw(Vector2 pos, Color color, Align align);

#endif // DRAW_H
