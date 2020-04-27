#include "../include/sprite-manager.hpp"
#include "../include/utils.hpp"
#include "../include/config.hpp"
#include <map>
#include <string>
#include <string_view>
#include <optional>
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/logging.h"
#include "../extern/beatsaber-hook/shared/utils/utils-functions.h"

// Iterations to busy-wait until loading (a single sprite) is considered failed
#define TIMEOUT 50000000

std::unordered_map<std::string, sprite_pair_t> SpriteManager::sprites;

void SpriteManager::textureLoaded(texture_complete_t* completeWrapper) {
    ASSERT_MSG(completeWrapper, "texture_complete_t is nullptr in SpriteManager::textureLoaded!");
    auto content = il2cpp_utils::RunMethod("UnityEngine.Networking", "DownloadHandlerTexture", "GetContent", completeWrapper->webRequest).value_or(nullptr);
    ASSERT_MSG(content, "Failed to get texture content, or it was null!");
    log(INFO, "Finalizing load for texture: %s", completeWrapper->path.data());
    auto val = sprites.find(completeWrapper->path);
    ASSERT_MSG(val != sprites.end(), "Could not find completeWrapper path when finalizing textureLoaded!");
    auto width = *RET_V_UNLESS(il2cpp_utils::GetPropertyValue<int>(content, "width"));
    auto height = *RET_V_UNLESS(il2cpp_utils::GetPropertyValue<int>(content, "height"));
    auto rect = (Rect){0.0f, 0.0f, (float)width, (float)height};
    auto pivot = (Vector2){0.5f, 0.5f};
    // Sprite sprite = Sprite.Create(content, rect, pivot, 1024f, 1u, 0, Vector4.zero, false);
    Vector4 zero = (Vector4){0, 0, 0, 0};
    auto sprite = RET_V_UNLESS(il2cpp_utils::RunMethod("UnityEngine", "Sprite", "Create", content, rect, pivot, 1024.0f, 1u, 0, zero, false).value_or(nullptr));
    sprites[completeWrapper->path].loaded = true;
    sprites[completeWrapper->path].sprite = sprite;
    // Free malloc'd structure after
    free(completeWrapper);
}

void SpriteManager::Initialize(HSVConfig config) {
    for (auto s : config.GetAllImagePaths()) {
        if (!LoadTexture(s)) {
            log(WARNING, "Could not load texture file: %s skipping it!", s.data());
            continue;
        }
        // TODO: Optimally, we load these on a separate thread, joining the unity thread only as needed
        // However, that doesn't seem feasible without a coroutine, so for now, we will busy wait.
        for (int i = 0; i < TIMEOUT && !sprites[s].loaded; i++) {
            // Wait
            if (i % 1000000 == 0) {
                log(DEBUG, "Waiting: %d / %d", i, TIMEOUT);
            }
        }
    }
}

void SpriteManager::Clear() {
    sprites.clear();
}

std::optional<Il2CppObject*> SpriteManager::GetSprite(std::string path) {
    auto found = sprites.find(path);
    if (found == sprites.end()) {
        // We didn't find it. Let's attempt to load it so when we try to get it later we get it.
        log(DEBUG, "Attempting to load texture: %s", path.data());
        RET_NULLOPT_UNLESS(LoadTexture(path));
        return std::nullopt;
    }
    if (!found->second.loaded) {
        // It isn't loaded, but it exists. We need to wait for it to be loaded.
        log(INFO, "Waiting for texture at: %s to load before returning a valid one.", path.data());
        return std::nullopt;
    }
    log(DEBUG, "Got sprite! Path: %s", path.data());
    return found->second.sprite;
}

bool SpriteManager::LoadTexture(std::string path) {
    log(INFO, "Loading texure: %s", path.data());
    if (!fileexists(path.data())) {
        log(ERROR, "File: %s does not exist!", path.data());
        return false;
    }
    auto requestPath = il2cpp_utils::createcsstr(std::string("file:///") + path);
    auto webRequest = il2cpp_utils::RunMethod("UnityEngine.Networking", "UnityWebRequestTexture", "GetTexture", requestPath).value_or(nullptr);
    RET_F_UNLESS(webRequest);
    // Create completeWrapper
    log(DEBUG, "Performing malloc for texture_complete_t!");
    texture_complete_t* completeWrapper = reinterpret_cast<texture_complete_t*>(malloc(sizeof(texture_complete_t)));
    log(DEBUG, "malloc success: %p", completeWrapper);
    completeWrapper->path = path;
    completeWrapper->webRequest = webRequest;
    // Create completion action
    // TODO: Check to see if this happens too slowly, perhaps we need to create the action before sending the request?
    log(DEBUG, "Sending web request...");
    auto asyncOperation = RET_F_UNLESS(il2cpp_utils::RunMethod(webRequest, "SendWebRequest").value_or(nullptr));
    log(DEBUG, "Web request sent!");
    auto field = RET_F_UNLESS(il2cpp_utils::FindField(asyncOperation, "m_completeCallback"));
    auto action = RET_F_UNLESS(il2cpp_utils::MakeAction(field, completeWrapper, textureLoaded));
    if (!il2cpp_utils::SetFieldValue(asyncOperation, field, action))
    {
        return false;
    }
    log(INFO, "Began loading texture!");
    sprites[path] = {false, nullptr};
    return true;
}