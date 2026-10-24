#ifndef gamecontext_h_included
#define gamecontext_h_included

#include "playdateSquad.h"
#include "particleManager.h"
#include "poolManager.h"

typedef struct GameState GameState;

typedef struct GameContext
{
    unsigned int gameElapsedMS;
    unsigned int frameCount;

    // Game state data
    unsigned int currentStateTimeoutMS; // Used for title attract states
    GameState *currentState;            // Current state of the context

    // Game data
    PoolManager *poolManager; // This is a large struct, hence a pointer
    ParticleManager particleManager;

    // Utilities and assets
    MELCrankIndicator *crankIndicator;
    LCDFont *font;
    PdxInfo pdxInfo;
} GameContext;

#endif