#include "SE_Draw.h"
#include "SE_Math.h"

static inline void SE_DrawPoint_Fast(SE_Surface *surface, int x, int y, u32 color)
{
    ((u32 *)surface->data)[x + y * surface->step] = color;
}

static inline void SE_DrawPoint(SE_Surface *surface, int x, int y, u32 color)
{
    if (    x >= 0 && x < surface->w
            && y >= 0 && y < surface->h)
    {
        SE_DrawPoint_Fast(surface, x, y, color);
    }
}

void SE_DrawLine(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color)
{
    int w = x1 - x0;
    int h = y1 - y0;

    int length = SE_MaxInt(abs(w), abs(h));
    if (length > 0) {
        f32 sx = (f32)w / (f32)length;
        f32 sy = (f32)h / (f32)length;

        f32 px = (f32)x0 + 0.5f; /* + 0.5 used for ceiling */
        f32 py = (f32)y0 + 0.5f;

        for (int i = 0; i < length; ++i) {
            SE_DrawPoint(surface, (int)px, (int)py, color);

            px += sx;
            py += sy;
        }
    }
}

void SE_FillRect(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color)
{
    if (x0 > x1) { SE_SwapInt(&x0, &x1); }
    if (y0 > y1) { SE_SwapInt(&y0, &y1); }

    x0 = SE_MaxInt(x0, 0);
    y0 = SE_MaxInt(y0, 0);
    x1 = SE_MinInt(x1, surface->w);
    y1 = SE_MinInt(y1, surface->h);

    int h = y1 - y0;
    int w = x1 - x0;

    u32 *data = &((u32 *)surface->data)[x0 + y0 * surface->step];

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            data[x] = color;
        }
        data += surface->step;
    }
}