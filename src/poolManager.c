#include "poolManager.h"
#include "genericPool.h"
#include "gameBridge.h"
#include "pdAssert.h"

// Include headers for your actual item types and their init/deinit functions
#include "gameContext.h"
#include "command.h"
#include "particle.h"

#include <assert.h>
// Validate each struct starts with an IntrusiveListNode member
static_assert(offsetof(Particle, listNode) == 0, "IntrusiveListNode must be first member of Particle");
static_assert(offsetof(Command, listNode) == 0, "IntrusiveListNode must be first member of Command");

// Static Storage for Items
static Particle particleArray[PARTICLE_POOLSIZE] = {0};
static Command commandArray[COMMAND_POOLSIZE] = {0};

// Item-specific init/deinit function prototypes (ensure these are defined elsewhere)
// These functions must match the 'item_init_func_t' and 'item_deinit_func_t' signatures
// (void* item, GameContext* context) and (void* item)

// PoolManager Implementation
void PoolManager_init(PoolManager *this, GameContext *context)
{
    pdAssert(this != NULL);
    this->gameContext = context; // Store context if needed by items

    // Initialize Particle Pool
    GenericPool_init(&this->particlePool, particleArray, sizeof(Particle), PARTICLE_POOLSIZE,
                     Particle_init, Particle_despawn, context);

    // Initialize Command Pool
    GenericPool_init(&this->commandPool, commandArray, sizeof(Command), COMMAND_POOLSIZE,
                     Command_init, Command_despawn, context);
}

// Particle
Particle *PoolManager_getParticle(PoolManager *this)
{
    pdAssert(this != NULL);
    return (Particle *)GenericPool_getItem(&this->particlePool);
}

void PoolManager_returnParticle(PoolManager *this, Particle *particle)
{
    pdAssert(this != NULL && particle != NULL);

    // This is deliberate, only return active nodes.
    IntrusiveListNode *node = (IntrusiveListNode *)particle;
    if (GenericPool_isItemActive(node))
    {
        GenericPool_returnItem(&this->particlePool, (IntrusiveListNode *)particle);
    }
}

void PoolManager_returnAllParticles(PoolManager *this)
{
#ifdef DEV_BUILD
    g_gameBridge->system_logToConsole(__func__);
#endif
    pdAssert(this != NULL);
    GenericPool_returnAllItems(&this->particlePool);
}

void PoolManager_iterateActiveParticles(PoolManager *this, bool (*callback)(Particle *p, void *userdata), void *userdata)
{
    pdAssert(this != NULL && callback != NULL);
    IntrusiveListNode *current_node = this->particlePool.activeHead;
    IntrusiveListNode *next_node;
    bool active;
    while (current_node)
    {
        // Capture next as we may be about to modify list for inactive particle - before callback
        next_node = current_node->next;

        active = callback((Particle *)current_node, userdata);
        if (!active)
        {
            // The current particle became inactive, remove it AFTER we have captured next node
            PoolManager_returnParticle(this, (Particle *)current_node);
        }
        current_node = next_node;
    }
}

// Command
Command *PoolManager_getCommand(PoolManager *this)
{
    pdAssert(this != NULL);
    return (Command *)GenericPool_getItem(&this->commandPool);
}

void PoolManager_returnCommand(PoolManager *this, Command *command)
{
    pdAssert(this != NULL && command != NULL);

    // This is deliberate, only return active nodes.
    IntrusiveListNode *node = (IntrusiveListNode *)command;
    if (GenericPool_isItemActive(node))
    {
        GenericPool_returnItem(&this->commandPool, (IntrusiveListNode *)command);
    }
}

void PoolManager_returnAllCommands(PoolManager *this)
{
#ifdef DEV_BUILD
    g_gameBridge->system_logToConsole(__func__);
#endif
    pdAssert(this != NULL);
    GenericPool_returnAllItems(&this->commandPool);
}

void PoolManager_iterateActiveCommands(PoolManager *this, bool (*callback)(Command *cmd, void *userdata), void *userdata)
{
    pdAssert(this != NULL && callback != NULL);
    IntrusiveListNode *current_node = this->commandPool.activeHead;
    IntrusiveListNode *next_node;
    bool active;
    while (current_node)
    {
        // Capture next as we may be about to modify list for inactive command - before callback
        next_node = current_node->next;

        active = callback((Command *)current_node, userdata);
        if (!active)
        {
            // The current command became inactive, remove it AFTER we have captured next node
            PoolManager_returnCommand(this, (Command *)current_node);
        }
        current_node = next_node;
    }
}

int PoolManager_getCommandCount(PoolManager *this)
{
    pdAssert(this != NULL);
    return GenericPool_getInUse(&this->commandPool); // Return the count of active commands
}

void PoolManager_sanityCheck(PoolManager *this)
{
    GenericPool_sanityCheck(&this->particlePool);
    GenericPool_sanityCheck(&this->commandPool);
}

void PoolManager_logHighWater(PoolManager *this)
{
    g_gameBridge->system_logToConsole("Pool high water:\nparticle: %d\ncommand: %d\n",
                                      GenericPool_getHighWater(&this->particlePool),
                                      GenericPool_getHighWater(&this->commandPool));
}