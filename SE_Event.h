#ifndef SE_EVENT_H
#define SE_EVENT_H

#include "SE_System.h"
#include "SE_Surface.h"

typedef enum SE_EventType
{
    SE_EVENT_UNKNOWN = 0,

    SE_EVENT_INIT,
    SE_EVENT_QUIT,

    SE_EVENT_TICK,
    SE_EVENT_DRAW,
    SE_EVENT_SIZE,

    SE_EVENT_KEYBOARD_KEY_DOWN,
    SE_EVENT_KEYBOARD_KEY_UP,

    SE_EVENT_MOUSE_MOVE,
    SE_EVENT_MOUSE_BUTTON_DOWN,
    SE_EVENT_MOUSE_BUTTON_UP,

} SE_EventType;

typedef struct SE_Event
{
    SE_EventType type;

    union {
        struct { SE_Surface *surface; } draw;
        struct { int key; } keyboard;
        struct { f64 time; } tick;
    };

} SE_Event;

typedef int (SE_EventHandler)(SE_Event *event);

/* keyboard key-codes */
#define SE_KEYBOARD_KEY_NULL      '\0'
#define SE_KEYBOARD_KEY_CTRL       0x11
#define SE_KEYBOARD_KEY_BACKSPACE '\b'
#define SE_KEYBOARD_KEY_TAB       '\t'
#define SE_KEYBOARD_KEY_RETURN    '\r'
#define SE_KEYBOARD_KEY_ESCAPE    '\033'
#define SE_KEYBOARD_KEY_SPACE     ' '
#define SE_KEYBOARD_KEY_A         'A'
#define SE_KEYBOARD_KEY_B         'B'
#define SE_KEYBOARD_KEY_C         'C'
#define SE_KEYBOARD_KEY_D         'D'
#define SE_KEYBOARD_KEY_E         'E'
#define SE_KEYBOARD_KEY_F         'F'
#define SE_KEYBOARD_KEY_G         'G'
#define SE_KEYBOARD_KEY_H         'H'
#define SE_KEYBOARD_KEY_I         'I'
#define SE_KEYBOARD_KEY_J         'J'
#define SE_KEYBOARD_KEY_K         'K'
#define SE_KEYBOARD_KEY_L         'L'
#define SE_KEYBOARD_KEY_M         'M'
#define SE_KEYBOARD_KEY_N         'N'
#define SE_KEYBOARD_KEY_O         'O'
#define SE_KEYBOARD_KEY_P         'P'
#define SE_KEYBOARD_KEY_Q         'Q'
#define SE_KEYBOARD_KEY_R         'R'
#define SE_KEYBOARD_KEY_S         'S'
#define SE_KEYBOARD_KEY_T         'T'
#define SE_KEYBOARD_KEY_U         'U'
#define SE_KEYBOARD_KEY_V         'V'
#define SE_KEYBOARD_KEY_W         'W'
#define SE_KEYBOARD_KEY_X         'X'
#define SE_KEYBOARD_KEY_Y         'Y'
#define SE_KEYBOARD_KEY_Z         'Z'
#define SE_KEYBOARD_KEY_DELETE    '\177'

#endif