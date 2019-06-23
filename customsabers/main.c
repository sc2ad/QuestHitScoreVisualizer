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

cs_string PATH = "customSaber.bundle";


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