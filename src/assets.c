#include "assets.h"
#include "gameBridge.h"

LCDBitmap *Assets_bitmap[lastAssetsBitmap];
LCDBitmap *Assets_GetBitmap(AssetsBitmap asset)
{
    const char *err = NULL;

    if (Assets_bitmap[asset] == NULL)
    {
        Assets_bitmap[asset] = g_gameBridge->graphics_loadBitmap(Asset_bitmapNames[asset], &err);
        if (Assets_bitmap[asset] == NULL)
        {
            g_gameBridge->system_error("Bitmap '%s' could not be loaded: %s", Asset_bitmapNames[asset], err);
        }
    }

    return Assets_bitmap[asset];
}

LCDBitmapTable *Assets_bitmapTable[lastAssetsBitmapTable];
LCDBitmapTable *Assets_GetBitmapTable(AssetsBitmapTable asset)
{
    const char *err = NULL;

    if (Assets_bitmapTable[asset] == NULL)
    {
        Assets_bitmapTable[asset] = g_gameBridge->graphics_loadBitmapTable(Asset_bitmapTableNames[asset], &err);
        if (Assets_bitmapTable[asset] == NULL)
        {
            g_gameBridge->system_error("Bitmaptable '%s' could not be loaded: %s", Asset_bitmapTableNames[asset], err);
        }
    }

    return Assets_bitmapTable[asset];
}

AudioSample *Assets_audioSample[lastAssetAudioSample];
AudioSample *Assets_GetAudioSample(AssetsAudioSample asset)
{
    const char *err = NULL;

    if (Assets_audioSample[asset] == NULL)
    {
        Assets_audioSample[asset] = g_gameBridge->sound_sample_load(Asset_audioSampleNames[asset]);
        if (Assets_audioSample[asset] == NULL)
        {
            g_gameBridge->system_error("Sample '%s' could not be loaded: %s", Asset_audioSampleNames[asset], err);
        }
    }

    return Assets_audioSample[asset];
}

LCDFont *Assets_fonts[lastAssetFont];
LCDFont *Assets_GetFont(AssetsFont asset)
{
    const char *err = NULL;

    if (Assets_fonts[asset] == NULL)
    {
        Assets_fonts[asset] = g_gameBridge->graphics_loadFont(Asset_fontNames[asset], &err);
        if (Assets_fonts[asset] == NULL)
        {
            g_gameBridge->system_error("Font '%s' could not be loaded: %s", Asset_fontNames[asset], err);
        }
    }

    return Assets_fonts[asset];
}