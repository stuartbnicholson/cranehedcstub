#include "constants.h"
#include "command.h"
#include "gameBridge.h"
#include "gameContext.h"
#include "gameStateTitle.h"
#include "poolManager.h"

#include "serialCommand.h"

// See main.c, global GameContext
extern GameContext g_gameContext;

static char serialCommand[SERIAL_COMMAND_LENGTH + 1] = {0};

#ifdef DEV_SERIAL
// Serial Commands:
// ST: Change to State Title
// SE: Change to State End Level
bool SerialCallback_Command(void *data)
{
    switch (serialCommand[0])
    {
    case 'h':
    case 'H': // Pool high water dump
        PoolManager_logHighWater(g_gameContext.poolManager);
        break;
        break;
    case 's':
    case 'S': // Force a state change
    {
        // Force a state change
        switch (serialCommand[1])
        {
        case 't':
        case 'T':
            GameState_changeState(&g_gameContext, &GameStateTitle);
            break;
        }
    }
    break;
    default:
#ifdef DEV_BUILD
        g_gameBridge->system_logToConsole("Unknown serial command: %s", serialCommand);
#endif
        break;
    }

    // Clear command
    serialCommand[0] = '\0';

    return false; // Command completed
}

void SerialMessageCallback(const char *data)
{
#ifdef DEV_BUILD
    g_gameBridge->system_logToConsole("Serial message received: %s", data);
#endif

    // Check if a command is already pending
    if (serialCommand[0] == '\0')
    {
        // Copy the serial command data and add a Command so it's processed in game or title loop
        size_t len = strlen(data);
        len = len > SERIAL_COMMAND_LENGTH ? SERIAL_COMMAND_LENGTH : len;
        memcpy(serialCommand, data, len);
        serialCommand[len] = '\0';

        Command *cmd = PoolManager_getCommand(g_gameContext.poolManager);
        if (cmd)
        {
            // Update the distance map for the Player's new position
            Command_spawn(cmd, SerialCallback_Command, NULL);
        }
#ifdef DEV_BUILD
        else
        {
            g_gameBridge->system_logToConsole("%s: no free commands", __func__);
        }
#endif
    }
}
#endif