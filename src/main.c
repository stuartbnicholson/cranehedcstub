#include "pd_api.h"

#include "constants.h"
#include "command.h"
#include "gameContext.h"
#include "gameBridge.h"
#include "gameStateTitle.h"
#include "poolManager.h"
#include "serialCommand.h"

// Internal function decls
static int update(void *userdata);

// Singleton instances
PoolManager g_poolManager = {0};
GameContext g_gameContext = {.poolManager = &g_poolManager};

int eventHandler(PlaydateAPI *pd, PDSystemEvent event, uint32_t arg)
{
    (void)arg; // arg is currently only used for event = kEventKeyPressed

    switch (event)
    {
    case kEventInit:
    {
        GameBridge_init(pd);

        // If you set an update callback in the kEventInit handler, the system assumes the game is pure C
        g_gameBridge->system_setUpdateCallback(update, g_gameBridge);

#ifdef DEV_SERIAL
        g_gameBridge->system_setSerialMessageCallback(SerialMessageCallback);
#endif

        GameState_changeState(&g_gameContext, &GameStateTitle);
    }
    break;

    case kEventPause:
        break;

    case kEventTerminate:
        break;
    case kEventResume:
        break;
    default:
        break;
    }

    return 0;
}

static int update(void *userdata)
{
    g_gameContext.currentState->update(&g_gameContext);

    return 1;
}