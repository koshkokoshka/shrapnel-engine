#ifndef SE_SURFACE_H
#define SE_SURFACE_H

#include "SE_System.h"

typedef struct
{
    int w; // width
    int h; // height
    int d; // depth

    reg step;
    reg size;
    void **data;

} SE_Surface;

SE_Surface *SE_CreateSurface(int w, int h, int d);

void SE_DestroySurface(SE_Surface *surface);

#endif