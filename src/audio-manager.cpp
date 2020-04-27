#include "../include/audio-manager.hpp"
#include "../include/utils.hpp"
#include "../include/config.hpp"
#include <map>
#include <string>
#include <string_view>
#include <optional>
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/logging.h"
#include "../extern/beatsaber-hook/shared/utils/utils-functions.h"

std::unordered_map<std::string, clip_pair_t> AudioManager::audioClips;

// Gets the audio type from a path
int AudioManager::getAudioType(std::string path) {
    if (path.ends_with(".ogg")) {
        return 0xE;
    } else if (path.ends_with(".wav")) {
        return 0x14;
    } else if (path.ends_with(".mp3")) {
        return 0xD;
    }
    return 0;
}

void AudioManager::audioClipLoaded(audio_complete_t* completeWrapper) {
    ASSERT_MSG(completeWrapper, "audio_complete_t is nullptr in AudioManager::audioClipLoaded!");
    auto content = il2cpp_utils::RunMethod("UnityEngine.Networking", "DownloadHandlerAudioClip", "GetContent", completeWrapper->webRequest).value_or(nullptr);
    ASSERT_MSG(content, "Failed to get AudioClip content, or it was null!");
    log(INFO, "Finalizing load for AudioClip: %s", completeWrapper->path.data());
    auto val = audioClips.find(completeWrapper->path);
    ASSERT_MSG(val != audioClips.end(), "Could not find completeWrapper path when finalizing audioClipLoaded!");
    audioClips[completeWrapper->path].loaded = true;
    audioClips[completeWrapper->path].clip = content;
    // Free malloc'd structure after
    free(completeWrapper);
}

void AudioManager::Initialize(HSVConfig config) {
    for (auto s : config.GetAllSoundPaths()) {
        if (!LoadAudioClip(s)) {
            log(WARNING, "Could not load audio file: %s skipping it!", s.data());
        }
    }
}

void AudioManager::Clear() {
    audioClips.clear();
}

std::optional<Il2CppObject*> AudioManager::GetAudioClip(std::string path) {
    auto found = audioClips.find(path.data());
    if (found == audioClips.end()) {
        // We didn't find it. Let's attempt to load it so when we try to get it later we get it.
        log(DEBUG, "Attempting to load audio clip at: %s", path.data());
        RET_NULLOPT_UNLESS(LoadAudioClip(path));
        return std::nullopt;
    }
    if (!found->second.loaded) {
        // It isn't loaded, but it exists. We need to wait for it to be loaded.
        log(INFO, "Waiting for audio clip at: %s to load before returning a valid one.", path.data());
        return std::nullopt;
    }
    log(DEBUG, "Got audio clip! Path: %s", path.data());
    return found->second.clip;
}

bool AudioManager::LoadAudioClip(std::string path) {
    log(INFO, "Loading clip: %s", path.data());
    if (!fileexists(path.data())) {
        log(ERROR, "File: %s does not exist!", path.data());
        return false;
    }
    auto audioType = getAudioType(path);
    log(INFO, "Audio type: %d", audioType);
    auto requestPath = il2cpp_utils::createcsstr(std::string("file:///") + path);
    auto webRequest = il2cpp_utils::RunMethod("UnityEngine.Networking", "UnityWebRequestMultimedia", "GetAudioClip", requestPath, audioType).value_or(nullptr);
    RET_F_UNLESS(webRequest);
    // Create completeWrapper
    audio_complete_t* completeWrapper = reinterpret_cast<audio_complete_t*>(malloc(sizeof(audio_complete_t)));
    completeWrapper->path = path;
    completeWrapper->webRequest = webRequest;
    // Create completion action
    // TODO: Check to see if this happens too slowly, perhaps we need to create the action before sending the request?
    auto asyncOperation = RET_F_UNLESS(il2cpp_utils::RunMethod(webRequest, "SendWebRequest").value_or(nullptr));
    auto field = RET_F_UNLESS(il2cpp_utils::FindField(asyncOperation, "m_completeCallback"));
    auto action = RET_F_UNLESS(il2cpp_utils::MakeAction(field, completeWrapper, audioClipLoaded));
    if (!il2cpp_utils::SetFieldValue(asyncOperation, field, action))
    {
        return false;
    }
    log(INFO, "Began loading audio clip!");
    audioClips[path] = {false, nullptr};
    return true;
}
