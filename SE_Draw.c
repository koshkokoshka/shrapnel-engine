#include "SE_Draw.h"
#include "SE_Math.h"

void SE_DrawBuffer(SE_Surface *surface, int x0, int y0, int x1, int y1, void *data, reg step)
{
    /* prestep source buffer */
    u32 *src = data;
    if (y0 < 0) { src += -y0 * step; }
    if (x0 < 0) { src += -x0; }

    /* clamp in destination rect */
    if (x0 < 0) { x0 = 0; }
    if (y0 < 0) { y0 = 0; }
    if (x1 > surface->w) { x1 = surface->w; }
    if (y1 > surface->h) { y1 = surface->h; }

    u32 *dst = &((u32 *)surface->data)[x0 + y0 * surface->step];

    int h = y1 - y0;
    int w = x1 - x0;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            dst[x] = src[x];
        }
        dst += surface->step;
        src += step;
    }
}

void SE_DrawBuffer_Scaled(SE_Surface *surface, int x0, int y0, int x1, int y1, void *data, reg step, int w, int h)
{
    if (x0 > x1) { SE_SwapInt(&x0, &x1); } /* x0 must be less than x1 */
    if (y0 > y1) { SE_SwapInt(&y0, &y1); }

    /* prestep source buffer */
    f32 stepX = (f32)w / (f32)(x1 - x0);
    f32 stepY = (f32)h / (f32)(y1 - y0);

    f32 dx = 0; /* initial coordinates */
    f32 dy = 0;

    if (x0 < 0) { dx -= x0 * stepX; x0 = 0; } /* clamp in destination rect and prestep */
    if (y0 < 0) { dy -= y0 * stepY; y0 = 0; }
    if (x1 > surface->w) { x1 = surface->w; }
    if (y1 > surface->h) { y1 = surface->h; }

    u32 *src = data;
    u32 *dst = &((u32 *)surface->data)[x0 + y0 * surface->step];

    int dw = x1 - x0;
    int dh = y1 - y0;

    for (int y = 0; y < dh; ++y) {
        int s = (int)dy * step;
        f32 xx = dx;
        for (int x = 0; x < dw; ++x) {
            dst[x] = src[(int)xx + s];
            xx += stepX;
        }
        dst += surface->step;
        dy += stepY;
    }
}

void SE_DrawLine(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color)
{
    if (x0 == x1) {
        for (int y = y0; y < y1; ++y) {
            SE_DrawPoint(surface, x0, y, color);
        }
    } else if (y0 == y1) {
        for (int x = x0; x < x1; ++x) {
            SE_DrawPoint(surface, x, y0, color);
        }
    } else {
        int w = x1 - x0;
        int h = y1 - y0;

        int length = SE_MaxInt(SE_AbsInt(w), SE_AbsInt(h));
        if (length > 0) {

            f32 sx = (f32)w / (f32)length;
            f32 sy = (f32)h / (f32)length;

            f32 px = (f32)x0 + 0.5f; /* + 0.5 used for ceiling */
            f32 py = (f32)y0 + 0.5f;

            for (int i = 0; i < length; ++i) {
                int x = (int)px;
                int y = (int)py;
                SE_DrawPoint(surface, x, y, color);

                px += sx;
                py += sy;
            }
        }
    }
}

void SE_DrawRect(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color)
{
    int l = (x0 >= 0) && (x0 < surface->w);
    int r = (x1 >= 0) && (x1 < surface->w);
    int t = (y0 >= 0) && (y0 < surface->h);
    int b = (y1 >= 0) && (y1 < surface->h);

    x0 = SE_MaxI32(x0, 0);
    x1 = SE_MinI32(x1, surface->w);
    y0 = SE_MaxI32(y0, 0);
    y1 = SE_MinI32(y1, surface->h);

    if (l) {
        for (int y = y0; y < y1; ++y) {
            ((u32 *)surface->data)[x0 + y * surface->step] = color;
        }
    }
    if (r) {
        for (int y = y0; y < y1; ++y) {
            ((u32 *)surface->data)[x1 + y * surface->step] = color;
        }
    }
    if (t) {
        for (int x = x0; x < x1; ++x) {
            ((u32 *)surface->data)[x + y0 * surface->step] = color;
        }
    }
    if (b) {
        for (int x = x0; x < x1; ++x) {
            ((u32 *)surface->data)[x + y1 * surface->step] = color;
        }
    }
}

void SE_FillRect(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color)
{
    if (x0 > x1) { SE_SwapInt(&x0, &x1); }
    if (y0 > y1) { SE_SwapInt(&y0, &y1); }

    /* clamp in destination rect */
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