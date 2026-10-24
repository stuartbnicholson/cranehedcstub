#ifndef constants_h_included
#define constants_h_included

#include "pd_api.h"

#define TARGET_FPS 50
#define TARGET_FRAME_S (1.0f / TARGET_FPS)
#define TARGET_FRAME_MS (1000.0f / TARGET_FPS)

// Logging and other safety checks
// #define DEV_BUILD 1

// Draw debug details onscreen
// #define DEV_DRAW 1

// Enable serial port communication for dev builds
#define DEV_SERIAL 1

// Fixed random seed vs time based seed
// #define DEV_FIXED_SEED 823819156

// Show FPS count in the corner of the screen
// #define DEV_SHOWFPS 1

// Sprite tags
typedef enum SpriteTag : uint8_t
{
    NoSpriteTag = 0,
} SpriteTag;

#endif