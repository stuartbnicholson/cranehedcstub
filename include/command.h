#ifndef command_h_included
#define command_h_included

#include "intrusiveList.h"

typedef struct GameContext GameContext;

typedef bool (*CommandExecute)(void *receiver);

// Simple Command pattern in C
typedef struct Command
{
    // MUST ALWAYS BE FIRST IN STRUCT so PoolManager can cast this to IntrusiveListNode*
    IntrusiveListNode listNode;

    CommandExecute execute;
    void *receiver;
} Command;

void Command_init(void *commandPtr, GameContext *context);
void Command_spawn(Command *this, CommandExecute execute, void *receiver);
void Command_despawn(void *commandPtr);

#endif