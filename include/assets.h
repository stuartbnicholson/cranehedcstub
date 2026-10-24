#ifndef assets_h_included
#define assets_h_included

#include "pd_api.h"

static const char *Asset_bitmapNames[] = {
    "assets/CoreLibs/crank-notice-text",
    "assets/CoreLibs/crank-notice-bubble",
    NULL};

typedef enum AssetsBitmap : uint8_t
{
    crankNoticeTextBitmap,
    crankNoticeBubbleBitmap,
    lastAssetsBitmap
} AssetsBitmap;
LCDBitmap *Assets_GetBitmap(AssetsBitmap asset);

//-----------------------------------------------------

static const char *Asset_bitmapTableNames[] = {
    "assets/CoreLibs/crank-frames",
};

typedef enum AssetsBitmapTable : uint8_t
{
    crankFramesBitmapTable,
    lastAssetsBitmapTable
} AssetsBitmapTable;
LCDBitmapTable *Assets_GetBitmapTable(AssetsBitmapTable asset);

//-----------------------------------------------------

static const char *Asset_audioSampleNames[] = {
    NULL,
    NULL};

typedef enum AssetsAudioSample : uint8_t
{
    noneSample,
    lastAssetAudioSample
} AssetsAudioSample;
AudioSample *Assets_GetAudioSample(AssetsAudioSample asset);

//-----------------------------------------------------

static const char *Asset_fontNames[] = {
    "assets/fonts/ammolite_10"};

typedef enum AssetsFont : uint8_t
{
    ammolite10Font,
    lastAssetFont
} AssetsFont;
LCDFont *Assets_GetFont(AssetsFont asset);

#endif