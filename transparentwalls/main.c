#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#include "../beatsaber-hook/shared/inline-hook/inlineHook.h"
#include "../beatsaber-hook/shared/utils/utils.h"

#undef log
#define log(...) __android_log_print(ANDROID_LOG_INFO, "QuestHook", "[TransparentWalls] " __VA_ARGS__)

// MAKE_HOOK(Camera_get_main, 0xC2F6D4, void* camera, void) {
//     log("Entering Camera.get_main...");
//     return Camera_get_main();
// }

MAKE_HOOK(Camera_get_cullingMask, 0xC2DF20, int, void* camera) {
    log("Entering Camera.get_cullingMask hook...");
    return Camera_get_cullingMask(camera);
}

MAKE_HOOK(Camera_set_cullingMask, 0xC2DFB0, void, void* camera, int value) {
    log("Entering Camera.set_cullingMask hook...");
    Camera_set_cullingMask(camera, value);
    log("Completed Camera.set_cullingMask!");
}

MAKE_HOOK(ObstacleController_ctor, 0x13B0C60, void, void* self) {
    log("Entering ObstacleController.ctor...");
    log("Attemping to get Camera...");
    void* (*fun_ptr)(void) = (void*)getRealOffset(0xC2F6D4);
    void* cam = (*fun_ptr)();
    log("Attempting to get old culling mask...");
    int mask = Camera_get_cullingMask(cam);
    log("Attempting to transform Camera culling mask...");
    mask |= (1 << 25);
    log("Attempting to call Camera.set_cullingMask...");
    Camera_set_cullingMask(cam, mask);
    log("Completed ObstacleController.ctor!");
}

__attribute__((constructor)) void lib_main()
{
    log("Installing Transparent Walls hooks...");
    log("Installing ObstacleController.ctor hook!");
    INSTALL_HOOK(ObstacleController_ctor);
    log("Installing Camera.get_cullingMask hook!");
    INSTALL_HOOK(Camera_get_cullingMask);
    log("Installing Camera.set_cullingMask hook!");
    INSTALL_HOOK(Camera_set_cullingMask);
    log("Completed installing hooks!");
}