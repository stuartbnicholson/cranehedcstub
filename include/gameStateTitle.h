#ifndef gameStateTitle_h_included
#define gameStateTitle_h_included

#include "pd_api.h"

#include "gameState.h"

#define GAMESTATETITLE_TIMEOUT_MS 6000

// Game title state
void GameStateTitle_Enter(GameContext *context);
void GameStateTitle_Update(GameContext *context);
void GameStateTitle_Exit(GameContext *context);

extern GameState GameStateTitle;

#endif