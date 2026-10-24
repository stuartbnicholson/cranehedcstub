#include "constants.h"
#include "assets.h"
#include "command.h"
#include "gameStateCommon.h"
#include "gameStateGame.h"
#include "gameBridge.h"
#include "serialCommand.h"
#include "uint32StringEncoder.h"
#include "utility.h"

#include "gameStateTitle.h"

GameState GameStateTitle = {GameStateTitle_Enter, GameStateTitle_Update, GameStateTitle_Exit};

// Internal function decls

void GameStateTitle_Enter(GameContext *context)
{
#ifdef DEV_BUILD
    g_gameBridge->system_logToConsole(__func__);
#endif

    context->currentStateTimeoutMS = g_gameBridge->system_getCurrentTimeMilliseconds() + GAMESTATETITLE_TIMEOUT_MS;

    // Seed the fast RNG
    uint32_t seed = 0;
#ifdef DEV_FIXED_SEED
    seed = DEV_FIXED_SEED;
#else
    seed = g_gameBridge->system_getSecondsSinceEpoch(NULL);
#endif
    // Log seed regardless
    char encodedSeed[ENCODED_UINT32STRING_LENGTH] = {0};
    g_gameBridge->system_logToConsole("Random seed: %d, \"%s\"", seed, Uint32ToString(seed, encodedSeed));
    RandomSeed(seed);

    context->crankIndicator = MELCrankIndicatorConstructor(true);
    context->font = Assets_GetFont(ammolite10Font);
    g_gameBridge->graphics_setFont(context->font);

    PoolManager_init(context->poolManager, context);
    ParticleManager_init(&context->particleManager, context);

    GameStateCommon_drawTitle(context);
}

#ifdef DEV_SERIAL
static bool Command_serialCallback(Command *cmd, void *userdata)
{
    if (cmd->execute == SerialCallback_Command)
    {
        return cmd->execute(cmd->receiver);
    }

    return false; // Command completed
}
#endif

static void GameStateTitle_UpdateTitleLevel(GameContext *context)
{
    // This is a butchered version of GameStateGame_Update
    context->gameElapsedMS = g_gameBridge->system_getCurrentTimeMilliseconds();
    context->frameCount++;

    g_gameBridge->sprite_updateAndDrawSprites();
    ParticleManager_update(&context->particleManager, context->gameElapsedMS);
}

void GameStateTitle_Update(GameContext *context)
{
    GameStateTitle_UpdateTitleLevel(context);

    if (GameStateCommon_input(context))
    {
        GameState_changeState(context, &GameStateGame);
    }
}

void GameStateTitle_Exit(GameContext *context)
{
#ifdef DEV_BUILD
    g_gameBridge->system_logToConsole(__func__);
#endif
}