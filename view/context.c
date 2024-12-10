#include "context.h"
#include "raylib.h"

Context context_get() {
    Context ctx = {0};
    ctx.mouse.x = GetMouseX();
    ctx.mouse.y = GetMouseY();
    ctx.mouse_clicked = IsMouseButtonDown(0);
    return ctx;
}
