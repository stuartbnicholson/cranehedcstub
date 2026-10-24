#ifndef gamestate_h_included
#define gamestate_h_included

#include "gameContext.h"

typedef struct GameState
{
    void (*enter)(GameContext *);  // Function pointer for entering the state
    void (*update)(GameContext *); // Function pointer for executing the state logic
    void (*exit)(GameContext *);   // Function pointer for exiting the state
} GameState;

void GameState_changeState(GameContext *context, GameState *newState);

#endif