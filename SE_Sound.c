#include "SE_Sound.h"

SE_Sound* SE_CreateSound(int frequency, int depth, int channels)
{
//    SE_Sound* sound = malloc(sizeof(SE_Sound));
//    if (sound) {
//        sound->frequency = frequency;
//        sound->depth = depth;
//        sound->channels = channels;
//        if (sound->data) {
//            return sound;
//        }
//        free(sound);
//    }
    return nil;
}

void SE_DestroySound(SE_Sound* sound)
{
    if (sound->data) {
        free(sound->data);
    }
    free(sound);
}

SE_Sound* SE_LoadSound(SE_Stream* stream)
{
    if (stream) {
        SE_Sound* sound = malloc(sizeof(SE_Sound));
        if (sound) {

            u32 tmp;
            stream->vTable->Read(stream, &tmp, 4); /* riff chunk id */
            stream->vTable->Read(stream, &tmp, 4); /* riff chunk size */
            stream->vTable->Read(stream, &tmp, 4); /* format */

            stream->vTable->Read(stream, &tmp, 4); /* fmt chunk id  */
            stream->vTable->Read(stream, &tmp, 4); /* fmt chunk size */
            stream->vTable->Read(stream, &tmp, 2); /* format */

            u16 channels;
            stream->vTable->Read(stream, &channels, 2);
            sound->channels = channels;

            u32 frequency;
            stream->vTable->Read(stream, &frequency, 4);
            sound->frequency = frequency;

            stream->vTable->Read(stream, &tmp, 4); /* byte rate  */
            stream->vTable->Read(stream, &tmp, 2); /* block align */

            u16 depth;
            stream->vTable->Read(stream, &depth, 2);
            sound->depth = depth;

            stream->vTable->Read(stream, &tmp, 4); /* data chunk id */

            u32 size;
            stream->vTable->Read(stream, &size, 4);
            sound->size = size;

            if (sound->size > 0) {
                sound->data = malloc(sound->size);
                if (sound->data) {
                    if (stream->vTable->Read(stream, sound->data, sound->size) == sound->size) {
                        return sound;
                    }
                    free(sound->data);
                }
            }
            free(sound);
        }
        stream->vTable->Close(stream);
    }
    return nil;
}
