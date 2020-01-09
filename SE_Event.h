#ifndef SE_EVENT_H
#define SE_EVENT_H

#include "SE_System.h"
#include "SE_Surface.h"

typedef enum SE_EventType
{
    SE_EVENT_TYPE_UNKNOWN = 0,

    SE_EVENT_TYPE_INIT,
    SE_EVENT_TYPE_QUIT,

    SE_EVENT_TYPE_TICK,
    SE_EVENT_TYPE_DRAW,
    SE_EVENT_TYPE_SIZE,

    SE_EVENT_TYPE_KEYBOARD_KEY_DOWN,
    SE_EVENT_TYPE_KEYBOARD_KEY_UP,

    SE_EVENT_TYPE_MOUSE_MOVE,
    SE_EVENT_TYPE_MOUSE_BUTTON_DOWN,
    SE_EVENT_TYPE_MOUSE_BUTTON_UP,

} SE_EventType;

typedef struct SE_Event
{
    SE_EventType type;

    union {
        struct { SE_Surface *surface; } draw;
    };

} SE_Event;

#endif