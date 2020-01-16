//#include <windows.h>

////-------------------------------------------------------------------
//// ConfigureAudioStream
////
//// Selects an audio stream from the source file, and configures the
//// stream to deliver decoded PCM audio.
////-------------------------------------------------------------------
//
//HRESULT ConfigureAudioStream(
//        IMFSourceReader *pReader,   // Pointer to the source reader.
//        IMFMediaType **ppPCMAudio   // Receives the audio format.
//)
//{
//    IMFMediaType *pUncompressedAudioType = NULL;
//    IMFMediaType *pPartialType = NULL;
//
//    // Select the first audio stream, and deselect all other streams.
//    HRESULT hr = pReader->SetStreamSelection(
//            (DWORD)MF_SOURCE_READER_ALL_STREAMS, FALSE);
//
//    if (SUCCEEDED(hr))
//    {
//        hr = pReader->SetStreamSelection(
//                (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, TRUE);
//    }
//
//    // Create a partial media type that specifies uncompressed PCM audio.
//    hr = MFCreateMediaType(&pPartialType);
//
//    if (SUCCEEDED(hr))
//    {
//        hr = pPartialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
//    }
//
//    if (SUCCEEDED(hr))
//    {
//        hr = pPartialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
//    }
//
//    // Set this type on the source reader. The source reader will
//    // load the necessary decoder.
//    if (SUCCEEDED(hr))
//    {
//        hr = pReader->SetCurrentMediaType(
//                (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM,
//                NULL, pPartialType);
//    }
//
//    // Get the complete uncompressed format.
//    if (SUCCEEDED(hr))
//    {
//        hr = pReader->GetCurrentMediaType(
//                (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM,
//                &pUncompressedAudioType);
//    }
//
//    // Ensure the stream is selected.
//    if (SUCCEEDED(hr))
//    {
//        hr = pReader->SetStreamSelection(
//                (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM,
//                TRUE);
//    }
//
//    // Return the PCM format to the caller.
//    if (SUCCEEDED(hr))
//    {
//        *ppPCMAudio = pUncompressedAudioType;
//        (*ppPCMAudio)->AddRef();
//    }
//
//    SafeRelease(&pUncompressedAudioType);
//    SafeRelease(&pPartialType);
//    return hr;
//}