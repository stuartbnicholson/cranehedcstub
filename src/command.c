#include "gameContext.h"
#include "pdAssert.h"

#include "command.h"

void Command_init(void *commandPtr, GameContext *context)
{
#ifdef DEV_MEMSET
    memset(commandPtr, 0, sizeof(Command));
#endif
}

void Command_spawn(Command *this, CommandExecute execute, void *receiver)
{
    pdAssert(this);

    this->execute = execute;
    this->receiver = receiver;
}

void Command_despawn(void *commandPtr)
{
    Command *this = commandPtr;

    this->execute = NULL;
    this->receiver = NULL;
}
