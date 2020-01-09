#include "SE_Surface.h"

SE_Surface *SE_CreateSurface(int w, int h, int d)
{
    SE_Surface *surface = malloc(sizeof(SE_Surface));
    if (surface) {
        surface->w = w;
        surface->h = h;
        surface->d = d;
        surface->step = w;
        surface->size = w * h * d;
        surface->data = malloc(surface->size);
        if (surface->data) {
            return surface;
        }
        free(surface);
    }
    return nil;
}

void SE_DestroySurface(SE_Surface *surface)
{
    if (surface->data) {
        free(surface->data);
    }
    free(surface);
}