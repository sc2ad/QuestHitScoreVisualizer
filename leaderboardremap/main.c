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
#include "../beatsaber-hook/shared/utils/utils.h"

#undef log
#define log(...) __android_log_print(ANDROID_LOG_INFO, "QuestHook", "[LeaderboardRemap] " __VA_ARGS__)

// So it seems possible to modify which leaderboard is showing (ex: Show a leaderboard for a different default song)
// Let's change the GetScores behavior to always show a particular beatmap.
// This involves string remapping, so hopefully this works :)

const char toReplace[] = "BeThereForYou";

MAKE_HOOK(leaderboardsModel_GetLeaderboardID, 0x12B6D70, cs_string*, void* difficultyBeatmap) {
    log("Entering LeaderboardsModel.GetLeaderboardID...");
    // log("Attempting to get level from difficultyBeatmap...");
    // // BeatmapLevelSO.DifficultyBeatmap.get_level: 0x12B2390 PROBABLY RIGHT
    // void* (*get_level)(void*) = (void*)getRealOffset(0x12B2390);
    // void* level = get_level(difficultyBeatmap);
    // log("Attempting to get levelID from level...");
    // // BeatmapLevelSO.get_levelID: 0x129C154 PROBABLY RIGHT
    // cs_string* (*get_levelID)(void*) = (void*)getRealOffset(0x129C154);
    // cs_string* levelID = get_levelID(level);
    // LETS TRY SOME CRAZY STUFF
    log("Attempting to get original string...");
    cs_string* orig = leaderboardsModel_GetLeaderboardID(difficultyBeatmap);
    log("Attempting to malloc new C# string...");
    cs_string* newStr = malloc(sizeof(cs_string));
    log("Attempting to set new C# string's 'str' value...");
    setcsstr(newStr, toReplace);
    log("Attempting to replace old level ID with new using System.String.Replace...");
    // System.String.Replace: 0x97FF04
    cs_string* (*replace_str)(cs_string*, cs_string*) = (void*)getRealOffset(0x97FF04);
    cs_string* toRet = replace_str(orig, newStr);
    log("Freeing temporary string...");
    free(newStr);
    log("Returning replaced string!");
    return toRet;
}

__attribute__((constructor)) void lib_main()
{
    log("Inserting LeaderboardRemap...");
    INSTALL_HOOK(leaderboardsModel_GetLeaderboardID);
    log("Completed installing LeaderboardRemap!");
}