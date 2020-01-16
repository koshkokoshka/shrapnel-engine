#ifndef SE_SOUND_H
#define SE_SOUND_H

#include "SE_System.h"
#include "SE_Stream.h"

typedef struct SE_Sound
{
    int frequency;
    int depth;
    int channels;
    reg size;
    void **data;

} SE_Sound;

SE_Sound* SE_CreateSound(int frequency, int depth, int channels);

void SE_DestroySound(SE_Sound* sound);

SE_Sound* SE_LoadSound(SE_Stream* stream);

#endif