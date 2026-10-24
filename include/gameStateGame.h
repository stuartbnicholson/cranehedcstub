#ifndef gameStateGame_h_included
#define gameStateGame_h_included

#include "pd_api.h"

#include "gameState.h"

// Game is actively being played
void GameStateGame_Enter(GameContext *context);
void GameStateGame_Update(GameContext *context);
void GameStateGame_Exit(GameContext *context);

extern GameState GameStateGame;

#endif