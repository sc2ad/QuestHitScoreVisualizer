#include "../include/texture-manager.hpp"
#include "../include/utils.hpp"
#include <map>
#include <string>
#include <string_view>
#include <optional>
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/logging.h"
#include "../extern/beatsaber-hook/shared/utils/utils-functions.h"

std::map<std::string, texture_pair_t> TextureManager::textures;

void TextureManager::textureLoaded(texture_complete_t* completeWrapper) {
    ASSERT_MSG(completeWrapper, "texture_complete_t is nullptr in TextureManager::textureLoaded!");
    auto content = il2cpp_utils::RunMethod("UnityEngine.Networking", "DownloadHandlerAudioClip", "GetContent", completeWrapper->webRequest).value_or(nullptr);
    ASSERT_MSG(content, "Failed to get AudioClip content, or it was null!");
    log(INFO, "Finalizing load for AudioClip: %s", completeWrapper->path.data());
    auto val = textures.find(std::string(completeWrapper->path.data()));
    ASSERT_MSG(val != textures.end(), "Could not find completeWrapper path when finalizing textureLoaded!");
    textures[val->first].loaded = true;
    textures[val->first].texture = content;
    // Free malloc'd structure after
    free(completeWrapper);
}

void TextureManager::Initialize(std::vector<std::string>& paths) {
    for (auto s : paths) {
        if (!LoadTexture(s)) {
            log(WARNING, "Could not load audio file: %s skipping it!", s.data());
        }
    }
}

std::optional<Il2CppObject*> TextureManager::GetTexture(std::string_view path) {
    auto found = textures.find(std::string(path.data()));
    if (found == textures.end()) {
        // We didn't find it. Let's attempt to load it so when we try to get it later we get it.
        RET_NULLOPT_UNLESS(LoadTexture(path));
        return std::nullopt;
    }
    if (!found->second.loaded) {
        // It isn't loaded, but it exists. We need to wait for it to be loaded.
        log(INFO, "Waiting for audio clip at: %s to load before returning a valid one.", path.data());
        return std::nullopt;
    }
    return found->second.texture;
}

bool TextureManager::LoadTexture(std::string_view path) {
    log(INFO, "Loading texure: %s", path.data());
    if (!fileexists(path.data())) {
        log(ERROR, "File: %s does not exists!", path.data());
        return false;
    }
    auto requestPath = il2cpp_utils::createcsstr(std::string("file:///") + path.data());
    auto webRequest = il2cpp_utils::RunMethod("UnityEngine.Networking", "UnityWebRequestTexture", "GetTexture", requestPath).value_or(nullptr);
    RET_F_UNLESS(webRequest);
    // Create completeWrapper
    texture_complete_t* completeWrapper = reinterpret_cast<texture_complete_t*>(malloc(sizeof(texture_complete_t)));
    completeWrapper->path = path;
    completeWrapper->webRequest = webRequest;
    // Create completion action
    // TODO: Check to see if this happens too slowly, perhaps we need to create the action before sending the request?
    auto asyncOperation = RET_F_UNLESS(il2cpp_utils::RunMethod(webRequest, "SendWebRequest").value_or(nullptr));
    auto field = RET_F_UNLESS(il2cpp_utils::FindField(asyncOperation, "m_completeCallback"));
    auto action = RET_F_UNLESS(il2cpp_utils::MakeAction(field, completeWrapper, textureLoaded));
    if (!il2cpp_utils::SetFieldValue(asyncOperation, field, action))
    {
        return false;
    }
    log(INFO, "Began loading texture!");
    textures[std::string(path.data())] = {false, nullptr};
    return true;
}