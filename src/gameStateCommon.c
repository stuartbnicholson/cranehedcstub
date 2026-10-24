#include "constants.h"
#include "gameContext.h"
#include "gameBridge.h"
#include "pdAssert.h"

#include "gameStateCommon.h"

void GameStateCommon_drawTitle(GameContext *context)
{
    g_gameBridge->graphics_clear(kColorBlack);

    g_gameBridge->graphics_drawText("Title Here", 10, kUTF8Encoding, 100, 50);
    // g_gameBridge->graphics_drawBitmap(Assets_GetBitmap(titleBitmap), 0, 0, kBitmapUnflipped);

    g_gameBridge->graphics_drawText("by cranehed.itch.io 2026", 24, kASCIIEncoding, 175, 116);
}

void GameStateCommon_update(GameContext *context)
{
}

bool GameStateCommon_input(GameContext *context)
{
    static PDButtons lastPushed = 0x00;
    PDButtons currentButtons = 0x00;
    PDButtons pushed = 0x00;
    PDButtons released = 0x00;

    g_gameBridge->system_getButtonState(&currentButtons, &pushed, &released);

    // Check if any buttons that were pushed in previous frames are now released
    PDButtons validReleases = released & lastPushed;

    // Update tracking of pushed buttons
    lastPushed = (lastPushed | pushed) & ~released;

    return (validReleases != 0x00);
}