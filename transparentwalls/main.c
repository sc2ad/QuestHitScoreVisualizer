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
#define log(...) __android_log_print(ANDROID_LOG_INFO, "QuestHook", "[TransparentWalls v0.0.0.5] " __VA_ARGS__)

#define LIV_ctor_offset 0x136E7BC
#define StretchableCube_Awake_offset 0x12F05D4
#define Camera_get_cullingMask_offset 0xC2DF20
#define Camera_set_cullingMask_offset 0xC2DFB0
#define ObstacleController_ctor_offset 0x13B0C60
#define Component_get_gameObject_offset 0xC31C10
#define Gameobject_set_layer_offset 0xC76FD4
#define Gameobject_get_layer_offset 0xC76F48
#define Camera_get_main_offset 0xC2F6D4
#define LayerMask_get_value_offset 0x298B60
#define LayerMask_set_value_offset 0x298B68

#define WallLayer 25

// NOW JUST NEED TO FIGURE OUT THE LIV CAMERA STUFF
// LIV.SpectatorLayerMask foffset: 0x18
// LIV.ctor: 0x136E7BC
// Sadly, I don't know exactly how large LayerMask struct is
// I have the sneaking suspicion that it is larger than 4 bytes, but I could be wrong.
// Let's try it as 4 bytes for now, with good logging
// From the Ghidra dump, it looks like it is an undefined 4 (making me believe it is just one 4 byte int)
// It's also entirely possible that the LIV constructor is not good enough and that I need to do it later
MAKE_HOOK(LIV_ctor, LIV_ctor_offset, void, void* self) {
    log("Entering LIV.ctor hook...");
    log("Calling orig...");
    LIV_ctor(self);
    log("Attempting to get old layer mask...");
    // LayerFieldOffset is at 0x18 from the object.
    // So, cast self to an integer add 0x18.
    // This field holds a pointer to a struct: LayerMask
    // So, cast the value of this field to a pointer to an integer
    // Modify this integer to be the proper mask (because LayerMask is literally just an integer, because it is a struct)
    void** layerFieldOffset = (void**)(self) + 0x18;
    log("Original LIV LayerMask Pointer: %i", (int)layerFieldOffset);
    log("Attempting to get value of LIV LayerMask...");
    int (*get_value_layermask)(void*) = (void*)getRealOffset(LayerMask_get_value_offset);
    int originalValue = get_value_layermask(*layerFieldOffset);
    log("Original LIV layer value: %i", originalValue);
    log("Attempting to set new layer to be the OR between current and %i...", WallLayer);
    originalValue |= (1 << WallLayer);
    log("Attempting to set new layer to be the OR between current and 27...");
    originalValue |= (1 << 27);
    log("Modified LIV layer: %i", originalValue);
    void (*set_value_layermask)(void*, int) = (void*)getRealOffset(LayerMask_set_value_offset);
    set_value_layermask(*layerFieldOffset, originalValue);
    log("Completed LIV.ctor!");
}

// INTERESTED IN StrechableCube.Awake: 0x12F05D4
// WANT TO CALL THE GAMEOBJECT FIELD AND CHANGE ITS LAYER (THIS IS A FUNCTION, SO WE CAN CALL IT!)
// Component.get_gameObject: 0xC31C10
// can take gameObject field and get the field for layer and change it (might even be a property!)
// IT'S A PROPERTY, YAY! 0xC76FD4

MAKE_HOOK(StretchableCube_Awake, StretchableCube_Awake_offset, void, void* self) {
    log("Entering StretchableCube.Awake hook...");
    log("Calling orig...");
    StretchableCube_Awake(self);
    log("Attempting to get GameObject pointer...");
    void* (*get_go)(void*) = (void*)getRealOffset(Component_get_gameObject_offset);
    void* go = (*get_go)(self);
    log("Attempting to get old GameObject layer...");
    int (*get_layer)(void*) = (void*)getRealOffset(Gameobject_get_layer_offset);
    int oldLayer = get_layer(go);
    log("Attempting to set layer to %i from %i...", WallLayer, oldLayer);
    void (*set_layer)(void*, int) = (void*)getRealOffset(Gameobject_set_layer_offset);
    set_layer(go, WallLayer);
    log("Completed StretchableCube.Awake!");
}

MAKE_HOOK(ObstacleController_ctor, ObstacleController_ctor_offset, void, void* self) {
    log("Entering ObstacleController.ctor...");
    log("Attemping to get Camera...");
    void* (*Camera_get_main)(void) = (void*)getRealOffset(Camera_get_main_offset);
    void* cam = Camera_get_main();
    log("Attempting to get old culling mask...");
    int (*Camera_get_cullingMask)(void*) = (void*)getRealOffset(Camera_get_cullingMask_offset);
    int mask = Camera_get_cullingMask(cam);
    log("Attempting to transform Camera culling mask from: %i to: %i...", mask, mask & ~(1 << WallLayer));
    mask &= ~(1 << WallLayer);
    log("Attempting to call Camera.set_cullingMask...");
    void (*Camera_set_cullingMask)(void*, int) = (void*)getRealOffset(Camera_set_cullingMask_offset);
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
    log("Installing StretchableCube.Awake hook!");
    INSTALL_HOOK(StretchableCube_Awake);
    log("Completed installing hooks!");
}