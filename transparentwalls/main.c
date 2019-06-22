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

// NOW JUST NEED TO FIGURE OUT THE LIV CAMERA STUFF
// LIV.SpectatorLayerMask foffset: 0x18
// LIV.ctor: 0x136E7BC
// Sadly, I don't know exactly how large LayerMask struct is
// I have the sneaking suspicion that it is larger than 4 bytes, but I could be wrong.
// Let's try it as 4 bytes for now, with good logging
// From the Ghidra dump, it looks like it is an undefined 4 (making me believe it is just one 4 byte int)
// It's also entirely possible that the LIV constructor is not good enough and that I need to do it later
MAKE_HOOK(LIV_ctor, 0x136E7BC, void, void* self) {
    log("Entering LIV.ctor hook...");
    log("Calling orig...");
    LIV_ctor(self);
    log("Attempting to get old layer mask...");
    int toChange = *(int*)(self + 0x18) | (1 << 25);
    log("Attempting to set new layer to be the OR between current and 25...");
    *(int*)(self + 0x18) = toChange;
    log("Attempting to set new layer to be the OR between current and 27...");
    *(int*)(self + 0x18) = toChange | (1 << 27);
    log("Completed LIV.ctor!");
}

// INTERESTED IN StrechableCube.Awake: 0x12F05D4
// WANT TO CALL THE GAMEOBJECT FIELD AND CHANGE ITS LAYER (THIS IS A FUNCTION, SO WE CAN CALL IT!)
// Component.get_gameObject here: 0xC31C10
// can take gameObject field and get the field for layer and change it (might even be a property!)
// IT'S A PROPERTY, YAY! 0xC76FD4

MAKE_HOOK(StretchableCube_Awake, 0x12F05D4, void, void* self) {
    int layer = 25;
    log("Entering StretchableCube.Awake hook...");
    log("Calling orig...");
    StretchableCube_Awake(self);
    log("Attempting to get GameObject pointer...");
    void* (*get_go)(void*) = (void*)getRealOffset(0xC31C10);
    void* go = (*get_go)(self);
    log("Attempting to set layer...");
    void (*set_layer)(void*, int) = (void*)getRealOffset(0xC76FD4);
    set_layer(go, layer);
    log("Completed StretchableCube.Awake!");
}

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
    mask &= ~(1 << 25);
    log("Attempting to call Camera.set_cullingMask...");
    Camera_set_cullingMask(cam, mask);
    log("Completed ObstacleController.ctor!");
}

__attribute__((constructor)) void lib_main()
{
    log("Installing Transparent Walls hooks...");
    log("Installing LIV.ctor hook!");
    INSTALL_HOOK(LIV_ctor);
    log("Installing ObstacleController.ctor hook!");
    INSTALL_HOOK(ObstacleController_ctor);
    log("Installing Camera.get_cullingMask hook!");
    INSTALL_HOOK(Camera_get_cullingMask);
    log("Installing Camera.set_cullingMask hook!");
    INSTALL_HOOK(Camera_set_cullingMask);
    log("Installing StretchableCube.Awake hook!");
    INSTALL_HOOK(StretchableCube_Awake);
    log("Completed installing hooks!");
}