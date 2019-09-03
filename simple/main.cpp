#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <wchar.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#include "../beatsaber-hook/shared/inline-hook/inlineHook.h"

#define LOG_LEVEL CRITICAL | ERROR | WARNING | INFO | DEBUG

#define MOD_ID "Simple"
#define VERSION "1.0.0"

#include "../beatsaber-hook/shared/utils/utils.h"

#define RawScoreWithoutMultiplier_offset 0xA0DA14

MAKE_HOOK(rawScoreWithoutMultiplier, RawScoreWithoutMultiplier_offset, void, void* noteCutInfo, void* saberAfterCutSwingRatingCounter, int* beforeCut, int* afterCut, int* cutDistance) {
    log(DEBUG, "Called RawScoreWithoutMultiplier!");
    log(DEBUG, "Calling orig...");
    rawScoreWithoutMultiplier(noteCutInfo, saberAfterCutSwingRatingCounter, beforeCut, afterCut, cutDistance);
    log(DEBUG, "Score: %i", *beforeCut + *afterCut);
    log(DEBUG, "SUCCESS!");
}

__attribute__((constructor)) void lib_main()
{
    #ifdef __aarch64__
    log(INFO, "Is 64 bit!");
    #endif
    log(DEBUG, "Installing Simple Mod...");
    log(INFO, "Address of hook: 0x%lx", addr_rawScoreWithoutMultiplier);
    log(INFO, "Output of getRealOffset: 0x%lx", getRealOffset(addr_rawScoreWithoutMultiplier));
    INSTALL_HOOK(rawScoreWithoutMultiplier);
    log(DEBUG, "Installed RawScoreWithoutMultiplier Hook!");
}