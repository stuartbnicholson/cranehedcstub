#include "pd_api.h"

static int update(void *userdata)
{
    PlaydateAPI *pd = (PlaydateAPI *)userdata;

    pd->graphics->clear(kColorWhite);
    pd->graphics->drawText("Hello, Playdate!", 15, kASCIIEncoding, 10, 10);
    pd->system->drawFPS(0, 0);

    return 1;
}

int eventHandler(PlaydateAPI *pd, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // arg is currently only used for event = kEventKeyPressed

    switch (event)
    {
    case kEventInit:
    {
        // If you set an update callback in the kEventInit handler, the system assumes the game is pure C
        pd->system->setUpdateCallback(update, pd);
    }
    break;

    case kEventPause:
    case kEventTerminate:
    case kEventResume:
    default:
        break;
    }

    return 0;
}