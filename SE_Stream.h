#ifndef SE_STREAM_H
#define SE_STREAM_H

#include "SE_System.h"

typedef enum
{
    SE_STREAM_READ = 1,
    SE_STREAM_WRITE,
    SE_STREAM_SEEK

} SE_Stream_Flags;

typedef struct SE_Stream SE_Stream;

typedef struct
{
    void (*Close) (SE_Stream *self);
    reg   (*Read) (SE_Stream *self, void *buffer, reg size);
    reg  (*Write) (SE_Stream *self, void *buffer, reg size);
    reg   (*Seek) (SE_Stream *self, int size, int relative);

} SE_Stream_VTable;

struct SE_Stream
{
    SE_Stream_VTable *vTable;
    u8 flags;

    void *data;
};

SE_Stream *SE_OpenStream(const char *url, SE_Stream_Flags flags);

void SE_ReleaseStream(SE_Stream *stream);

#endif