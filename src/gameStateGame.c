#include "constants.h"
#include "gameBridge.h"
#include "particleManager.h"
#include "pdAssert.h"
#include "utility.h"

#include "gameStateGame.h"

GameState GameStateGame = {GameStateGame_Enter, GameStateGame_Update, GameStateGame_Exit};

// Internal function decls

void GameStateGame_Enter(GameContext *context)
{
#ifdef DEV_BUILD
    g_gameBridge->system_logToConsole(__func__);
#endif
}

void GameStateGame_Update(GameContext *context)
{
    context->gameElapsedMS = g_gameBridge->system_getCurrentTimeMilliseconds();
    context->frameCount++;

    g_gameBridge->graphics_setScreenClipRect(0, 0, 400, 240);

    g_gameBridge->sprite_updateAndDrawSprites();

    ParticleManager_update(&context->particleManager, context->gameElapsedMS);
}

void GameStateGame_Exit(GameContext *context)
{
#ifdef DEV_BUILD
    g_gameBridge->system_logToConsole(__func__);
#endif
}