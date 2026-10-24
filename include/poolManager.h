#ifndef poolManager_h_included
#define poolManager_h_included

#include "genericPool.h"

// Forward declare your item types
typedef struct Particle Particle;
typedef struct Command Command;

typedef struct GameContext GameContext;

// Define pool sizes (these could also be in specific item headers or a config file)
#define PARTICLE_POOLSIZE 40
#define COMMAND_POOLSIZE 20

typedef struct PoolManager
{
    GenericPool particlePool;
    GenericPool commandPool;

    GameContext *gameContext;
} PoolManager;

// Initialize a pre-allocated PoolManager instance
void PoolManager_init(PoolManager *this, GameContext *context);

// --- Item Access Functions (Type-Specific) ---
Particle *PoolManager_getParticle(PoolManager *this);
void PoolManager_returnParticle(PoolManager *this, Particle *particle);
void PoolManager_returnAllParticles(PoolManager *this);
void PoolManager_iterateActiveParticles(PoolManager *this, bool (*callback)(Particle *p, void *userdata), void *userdata);

Command *PoolManager_getCommand(PoolManager *this);
void PoolManager_returnCommand(PoolManager *this, Command *command);
void PoolManager_returnAllCommands(PoolManager *this);
void PoolManager_iterateActiveCommands(PoolManager *this, bool (*callback)(Command *cmd, void *userdata), void *userdata);
int PoolManager_getCommandCount(PoolManager *this);

void PoolManager_sanityCheck(PoolManager *this);
void PoolManager_logHighWater(PoolManager *this);

#endif