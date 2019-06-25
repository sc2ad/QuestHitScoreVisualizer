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
#define log(...) __android_log_print(ANDROID_LOG_INFO, "QuestHook", "[CustomSabers] " __VA_ARGS__)

// AssetBundle.LoadAsset<GameObject> doesn't exist as an offset?
// AssetBundle.LoadFromFileAsync(string path) 0x1278B44
// Ret: AssetBundleCreateRequest
// AssetBundleCreateRequest.get_assetBundle 0x1278D60

// Looks like it is all async operations now
// LoadAssetAsync(string name) 0x5CD740
// LoadAssetAsync(string name, Type type) 0x1278B68
// Ret: AssetBundleRequest
// AssetBundleRequest.get_asset 0x1278E08

// 0x5CD740: three parameters: (AssetBundle, string pointer, type pointer)
// Type pointer needs to be of type gameobject...

// Let's hook into the very beginning, when the health and safety screen is removed,
// or maybe when sabers are initially constructed?
// We could also do something funky like always do it until we have done it successfully

// Saber.Start: 0x481080

// From Unity Project, this is what a call to Resources.Load<GameObject>("_customsaber") looks like:
// Resources.Load(DAT_00708ad4,DAT_00701f6c);
// I THINK 00708ad4 is GameObject as opposed to 00701F6C (whch is "_customsaber")
// But because these are dynamically created, I have no idea what/where these are or how to learn.
// Can confirm that the first one is indeed GameObject
// Two additional calls to it: 006b8f64, 0070003c
// Can't find matching calls to these in dumps, they look like locations where DAT are held (pointers to DAT)


cs_string PATH = "customSaber.bundle";
int GO_TYPE = 

MAKE_HOOK(Saber_start, 0x481080, void, void* self) {
    log("Entering Saber.Start hook...");
    Saber_start(self);
    log("Attempting to get AssetBundleCreateRequest...");
    void* (*LoadFromFileAsync)(void*) = (void*)getRealOffset(0x1278B44);
    void* assetBundleCreateRequest = LoadFromFileAsync(&PATH);
    log("Attempting to get AssetBundle from AssetBundleCreateRequest...");
    void* (*get_assetBundle)(void*) = (void*)getRealOffset(0x1278D60);
    void* assetBundle = get_assetBundle(assetBundleCreateRequest);
    log("Attempting to get GameObject from assetBundle...");
    // Need to find the DAT object (int IL2CPP via ghidra) for the GameObject type
    void* (*loadAssetAsync)(void*, void*, void*) = (void*)getRealOffset(0x5CD740);
    void* gameobject = loadAssetAsync(assetBundle, "_customsaber", GO_TYPE);
}

__attribute__((constructor)) void lib_main()
{
    log("Installing Custom Sabers hooks...");

    log("Completed installing hooks!");
}