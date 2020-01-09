#define UNICODE
#include <windows.h>

#include <SE_System.h>
#include <SE_Event.h>

// user-code
int SE_Demo_HandleEvent(SE_Event *event)
{
    switch (event->type)
    {
        case SE_EVENT_TYPE_DRAW: {
            SE_Surface *surface = event->draw.surface;

            static int frame = 0;
            frame++;

            for (int y = 0; y < surface->h; ++y) {
                for (int x = 0; x < surface->w; ++x) {
                    u8 *data = &((u8 *)surface->data)[(x + y * surface->step) * surface->d];
                    for (int d = 0; d < surface->d; ++d) {
                        data[d] = x ^ (y + (frame * d));
                    }
                }
            }
        } break;

        default:
            return 1;
    }

    return 0;
}

// frame buffer
SE_Surface *fb;

// screen buffer descriptor
BITMAPINFO bmi = {
    .bmiHeader = {
        .biSize          = sizeof(BITMAPINFOHEADER),
        .biWidth         = 0,
        .biHeight        = 0,
        .biPlanes        = 1,
        .biBitCount      = sizeof(u32) * 8, // u32 = 32-bit color
        .biCompression   = 0,
        .biSizeImage     = 0,
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrUsed       = 0,
        .biClrImportant  = 0
    },
    .bmiColors = 0
};

// window event handling procedure
LRESULT CALLBACK SE_WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
        case WM_CREATE:
            SetTimer(hWnd, 0, 1000 / 120, NULL);
            break;

        case WM_DESTROY:
            if (fb) {
                SE_DestroySurface(fb);
            }
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            if (fb == nil) {
                bmi.bmiHeader.biWidth  = LOWORD(lParam);
                bmi.bmiHeader.biHeight = HIWORD(lParam);

                fb = SE_CreateSurface(bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, bmi.bmiHeader.biBitCount / 8);

                bmi.bmiHeader.biHeight *= -1; // negate height to flip an image
            }
            break;

        case WM_TIMER:
            RedrawWindow(hWnd, NULL, NULL, RDW_NOERASE | RDW_NOFRAME | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW);
            break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            if (BeginPaint(hWnd, &ps) != nil) {

                SE_Event event;
                event.type = SE_EVENT_TYPE_DRAW,
                event.draw.surface = fb;
                if (SE_Demo_HandleEvent(&event) == 0) {

                    StretchDIBits(ps.hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom,
                                  0, 0, fb->w, fb->h, fb->data, &bmi, DIB_RGB_COLORS, SRCCOPY);
                }

                EndPaint(hWnd, &ps);
                break;
            }
        } return 1;

        default:
            return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

    return 0;
}

// window class
WNDCLASS wc = {
    .style         = 0,
    .lpfnWndProc   = SE_WndProc,
    .cbClsExtra    = 0,
    .cbWndExtra    = 0,
    .hInstance     = 0,
    .hIcon         = 0,
    .hCursor       = 0,
    .hbrBackground = NULL,
    .lpszMenuName  = NULL,
    .lpszClassName = TEXT("SE_WND")
};

// window style
DWORD ws =    WS_OVERLAPPEDWINDOW
           & ~WS_THICKFRAME
           & ~WS_MAXIMIZEBOX;

// window rect
RECT  wr = {
    .left   = 0,
    .top    = 0,
    .right  = 640, // width
    .bottom = 480  // height
};

// win32 entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MSG msg;

    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    // register window class
    if (RegisterClass(&wc)) {

        // resize window to fit specific client-area size
        if (AdjustWindowRect(&wr, ws, (BOOL)wc.lpszMenuName)) {
            wr.right -= wr.left;
            wr.bottom -= wr.top;
            wr.left = (GetSystemMetrics(SM_CXSCREEN) - wr.right) / 2; // center the window
            wr.top = (GetSystemMetrics(SM_CYSCREEN) - wr.bottom) / 2;
        }

        // create window
        HWND hWnd = CreateWindow(wc.lpszClassName, TEXT("Shrapnel Engine"), ws,
                                 wr.left, wr.top, wr.right, wr.bottom,
                                 NULL, NULL, wc.hInstance, NULL);
        if (hWnd) {
            ShowWindow(hWnd, nShowCmd);

            // start event loop
            while (GetMessage(&msg, NULL, 0, 0)) {
                DispatchMessage(&msg);
            }

            DestroyWindow(hWnd);
        }

        UnregisterClass(wc.lpszClassName, wc.hInstance);
    }

    return msg.wParam; // should be 0, if no error
}