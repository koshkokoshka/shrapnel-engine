#ifndef SE_DRAW_H
#define SE_DRAW_H

#include "SE_System.h"
#include "SE_Surface.h"

void SE_DrawLine(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color);

void SE_FillRect(SE_Surface *surface, int x0, int y0, int x1, int y1, u32 color);

void SE_DrawTriangle(SE_Surface *surface, int x0, int y0, int x1, int y1, int x2, int y2, u32 color);

void SE_FillTriangle(SE_Surface *surface, int x0, int y0, int x1, int y1, int x2, int y2, u32 color);

#endif