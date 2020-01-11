#include "SE_Stream.h"

#include <windows.h>

#include "SE_Math.h" // MinI32

reg SE_Stream_File_Read(SE_Stream *self, void *buffer, reg size)
{
    DWORD read;
    ReadFile(self->data, buffer, size, &read, NULL);
    return read;
}

reg SE_Stream_File_Write(SE_Stream *self, void *buffer, reg size)
{
    DWORD written;
    WriteFile(self->data, buffer, size, &written, NULL);
    return written;
}

void SE_Stream_File_Close(SE_Stream *self)
{
    CloseHandle(self->data);
}

typedef struct
{
    HRSRC hResInfo;
    HGLOBAL *hRes;
    reg position;

} SE_Stream_Resource_Data;

SE_Stream_VTable SE_Stream_File_VTable = {
        .Close = SE_Stream_File_Close,
        .Read = SE_Stream_File_Read,
        .Write = SE_Stream_File_Write,
        .Seek = nil
};

void SE_Stream_Resource_Close(SE_Stream *self)
{
    SE_Stream_Resource_Data *data = self->data;
    if (data) {
        FreeResource(data->hRes);
        free(self->data);
    }
}

reg SE_Stream_Resource_Read(SE_Stream *self, void *buffer, reg size)
{
    reg read = 0;
    if (size > 0) {
        SE_Stream_Resource_Data *data = self->data;
        LPBYTE ptr = (LPBYTE)LockResource(data->hRes);
        if (ptr) {
            DWORD resSize = SizeofResource(GetModuleHandle(NULL), data->hResInfo);
            size = SE_MinInt(size, resSize - data->position);
            while (read < size) {
                reg i = data->position + read;
                ((LPBYTE)buffer)[read] = ptr[i];
                read++;
            }
            data->position += read;
        }
    }
    return read;
}

SE_Stream_VTable SE_Stream_Resource_VTable = {
        .Close = SE_Stream_Resource_Close,
        .Read = SE_Stream_Resource_Read,
        .Write = nil,
        .Seek = nil
};

SE_Stream *SE_OpenStream(const char *url, SE_Stream_Flags flags)
{
    if (url[0] == 'f' && url[1] == 'i' && url[2] == 'l' && url[3] == 'e') {

        DWORD access = 0;
        if (flags & SE_STREAM_READ) {
            access |= GENERIC_READ;
        }
        if (flags & SE_STREAM_WRITE) {
            access |= GENERIC_WRITE;
        }

        HANDLE hFile = CreateFile(&url[7], access, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            SE_Stream *stream = malloc(sizeof(SE_Stream));
            if (stream) {
                stream->vTable = &SE_Stream_File_VTable;
                stream->data = hFile;
                return stream;
            }
            CloseHandle(hFile);
        }

    } else if (url[0] == 'r' && url[1] == 'e' && url[2] == 's') {

        HRSRC hResInfo = FindResource(GetModuleHandle(NULL), &url[6], RT_RCDATA);
        if (hResInfo) {
            HGLOBAL hRes = LoadResource(GetModuleHandle(NULL), hResInfo);
            SE_Stream *stream = malloc(sizeof(SE_Stream));
            if (stream) {
                stream->vTable = &SE_Stream_Resource_VTable;
                stream->data = malloc(sizeof(SE_Stream_Resource_Data));
                if (stream->data) {
                    SE_Stream_Resource_Data *data = stream->data;
                    data->hResInfo = hResInfo;
                    data->hRes = hRes;
                    data->position = 0;
                    return stream;
                }
                free(stream);
            }
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
