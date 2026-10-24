#include "gameState.h"

void GameState_changeState(GameContext *context, GameState *newState)
{
    if (context->currentState != NULL && context->currentState->exit)
    {
        context->currentState->exit(context);
    }
    context->currentState = newState;
    if (context->currentState->enter)
    {
        context->currentState->enter(context);
    }
}