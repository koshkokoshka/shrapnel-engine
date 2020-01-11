#include "SE_Surface.h"

#include "SE_Stream.h"

#include <windows.h>
#include <wincodec.h>

SE_Surface *SE_LoadSurface(SE_Stream *stream)
{
    SE_Surface *surface = nil;

    IStream* pstm;
    if (SUCCEEDED(CreateStreamOnHGlobal(NULL, TRUE, &pstm))) {

        char buffer[1024 * 8];
        reg read;
        while ((read = stream->vTable->Read(stream, buffer, sizeof(buffer) / sizeof(buffer[0]))) > 0) {
            ULONG written;
            pstm->lpVtbl->Write(pstm, buffer, read, &written);
        }

        IWICImagingFactory* wicImagingFactory;
        if (SUCCEEDED(CoCreateInstance(&CLSID_WICImagingFactory, NULL, CLSCTX_INPROC, &IID_IWICImagingFactory, (LPVOID*)&wicImagingFactory))) {

            IWICBitmapDecoder* wicBitmapDecoder;
            if (SUCCEEDED(wicImagingFactory->lpVtbl->CreateDecoderFromStream(wicImagingFactory, pstm, NULL, WICDecodeMetadataCacheOnLoad, &wicBitmapDecoder))) {

                IWICBitmapFrameDecode* wicFrame;
                if (SUCCEEDED(wicBitmapDecoder->lpVtbl->GetFrame(wicBitmapDecoder, 0, &wicFrame))) {

                    IWICFormatConverter* wicFormatConverter;
                    if (SUCCEEDED(wicImagingFactory->lpVtbl->CreateFormatConverter(wicImagingFactory, &wicFormatConverter))) {

                        if (SUCCEEDED(wicFormatConverter->lpVtbl->Initialize(wicFormatConverter, (IWICBitmapSource*)wicFrame, &GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom))) {

                            UINT w, h;
                            if (SUCCEEDED(wicFormatConverter->lpVtbl->GetSize(wicFormatConverter, &w, &h))) {
                                surface = SE_CreateSurface((int)w, (int)h, 4);
                                if (surface) {
                                    UINT stride = w * 4;
                                    if (FAILED(wicFormatConverter->lpVtbl->CopyPixels(wicFormatConverter, NULL, stride, stride * h, (BYTE*)surface->data))) {
                                        SE_DestroySurface(surface);
                                        surface = nil;
                                    }
                                }
                            }
                        }
                        wicFormatConverter->lpVtbl->Release(wicFormatConverter);
                    }
                    wicFrame->lpVtbl->Release(wicFrame);
                }
                wicBitmapDecoder->lpVtbl->Release(wicBitmapDecoder);
            }
            wicImagingFactory->lpVtbl->Release(wicImagingFactory);
        }
    }

    return surface;
}