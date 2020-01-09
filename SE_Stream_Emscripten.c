#include "SE_Stream.h"

#include <emscripten.h>
#include <emscripten/html5.h>

#include <stdio.h>

reg SE_Stream_MEMFS_Read(SE_Stream *self, void *buffer, reg size)
{
    return fread(buffer, 1, size, self->data);
}

void SE_Stream_MEMFS_Close(SE_Stream *self)
{
    fclose(self->data);
}

reg SE_Stream_MEMFS_Seek(SE_Stream *self, int size, int relative)
{
    fseek(self->data, size, relative);
    return (reg)ftell(self->data);
}

SE_Stream_VTable SE_Stream_MEMFS_VTable = {
        .Close = SE_Stream_MEMFS_Close,
        .Read = SE_Stream_MEMFS_Read,
        .Write = nil,
        .Seek = SE_Stream_MEMFS_Seek
};

SE_Stream *SE_OpenStream(const char *url, SE_Stream_Flags flags)
{
    url = &url[6];

    if (flags == SE_STREAM_READ) {
        void *handle = fopen(url, "rb");
        if (handle) {
            SE_Stream *stream = malloc(sizeof(SE_Stream));
            stream->vTable = &SE_Stream_MEMFS_VTable;
            stream->data = handle;
            return stream;
        }
    }
    return nil;
}

void SE_ReleaseStream(SE_Stream *stream)
{
    if (stream) {
        if (stream->vTable) {
            stream->vTable->Close(stream);
        }
        free(stream);
    }
}