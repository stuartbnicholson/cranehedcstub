#ifndef gameStateCommon_h_included
#define gameStateCommon_h_included

#include "pd_api.h"

typedef struct GameContext GameContext;

void GameStateCommon_drawTitle(GameContext *context);

// Tap any button
bool GameStateCommon_input(GameContext *context);

#endif