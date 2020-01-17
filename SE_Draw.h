#ifndef SE_DRAW_H
#define SE_DRAW_H

#include "SE_System.h"
#include "SE_Surface.h"

void SE_DrawBuffer(SE_Surface *surface, int x0, int y0, int x1, int y1, void *data, reg step);

void SE_DrawBuffer_Scaled(SE_Surface *surface, int x0, int y0, int x1, int y1, void *data, reg step, int w, int h);

void SE_DrawLine(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color);

void SE_DrawRect(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color);

void SE_FillRect(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color);

void SE_DrawTriangle(SE_Surface *surface, int x0, int y0, int x1, int y1, int x2, int y2, u32 color);

void SE_FillTriangle(SE_Surface *surface, int x0, int y0, int x1, int y1, int x2, int y2, u32 color);

void SE_DrawRect_Dashed(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color, int step, int gaps);

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

#endif