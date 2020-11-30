#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include "../include/audio-manager.hpp"
#include "../include/utils.hpp"
#include "../include/config.hpp"
#include <map>
#include <string>
#include <string_view>
#include <optional>
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
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
    static auto logger = getLogger().WithContext("AudioManager").WithContext("audioClipLoaded");

    ASSERT_MSG(logger, completeWrapper, "audio_complete_t is nullptr in AudioManager::audioClipLoaded!");
    auto* content = il2cpp_utils::RunMethodUnsafe("UnityEngine.Networking", "DownloadHandlerAudioClip", "GetContent", completeWrapper->webRequest).value_or(nullptr);
    ASSERT_MSG(logger, content, "Failed to get AudioClip content, or it was null!");
    logger.info("Finalizing load for AudioClip: %s", completeWrapper->path.data());
    auto val = audioClips.find(completeWrapper->path);
    ASSERT_MSG(logger, val != audioClips.end(), "Could not find completeWrapper path when finalizing audioClipLoaded!");
    audioClips[completeWrapper->path].loaded = true;
    audioClips[completeWrapper->path].clip = content;
    // Call DontDestroyOnLoad
    ASSERT_MSG(logger, il2cpp_utils::RunMethodUnsafe("UnityEngine", "Object", "DontDestroyOnLoad", content), "Failed to call UnityEngine.Object.DontDestroyOnLoad(content)");
    // Destruct created structure after
    delete completeWrapper;
}

// Should be called at the start of a scene that all the audio clips will be used in
void AudioManager::Initialize(const HSVConfig& config) {
    static auto logger = getLogger().WithContext("AudioManager").WithContext("Initialize");
    if (audioPaths.size() == 0) {
        config.GetAllSoundPaths().swap(audioPaths);
    }
    for (auto s : audioPaths) {
        if (!LoadAudioClip(s)) {
            logger.warning("Could not load audio file: %s skipping it!", s.data());
        }
        // Delay, if necessary (?)
        usleep(100000);
    }
}

// Should be called after a scene transition, to ensure the audio clips are always valid
void AudioManager::Clear() {
    audioClips.clear();
}

std::optional<Il2CppObject*> AudioManager::GetAudioClip(std::string path) {
    static auto logger = getLogger().WithContext("AudioManager").WithContext("GetAudioClip");
    auto found = audioClips.find(path.data());
    if (found == audioClips.end()) {
        // We didn't find it. Let's attempt to load it so when we try to get it later we get it.
        logger.debug("Attempting to load audio clip at: %s", path.data());
        RET_NULLOPT_UNLESS(logger, LoadAudioClip(path));
        return std::nullopt;
    }
    if (!found->second.loaded) {
        // It isn't loaded, but it exists. We need to wait for it to be loaded.
        logger.info("Waiting for audio clip at: %s to load before returning a valid one.", path.data());
        return std::nullopt;
    }
    logger.debug("Got audio clip! Path: %s", path.data());
    return found->second.clip;
}

bool AudioManager::LoadAudioClip(std::string path) {
    static auto logger = getLogger().WithContext("AudioManager").WithContext("LoadAudioClip");
    if (audioClips.find(path) != audioClips.end()) {
        logger.info("Audio Clip: %s already exists!", path.data());
        return true;
    }
    logger.info("Loading clip: %s", path.data());
    if (!fileexists(path.data())) {
        logger.error("File: %s does not exist!", path.data());
        return false;
    }
    auto audioType = getAudioType(path);
    logger.info("Audio type: %d", audioType);
    auto requestPath = il2cpp_utils::createcsstr(std::string("file:///") + path);
    auto webRequest = il2cpp_utils::RunMethodUnsafe("UnityEngine.Networking", "UnityWebRequestMultimedia", "GetAudioClip", requestPath, audioType).value_or(nullptr);
    RET_F_UNLESS(logger, webRequest);
    // Create completeWrapper
    audio_complete_t* completeWrapper = new audio_complete_t();
    completeWrapper->path = path;
    completeWrapper->webRequest = webRequest;
    // Create completion action
    // TODO: Check to see if this happens too slowly, perhaps we need to create the action before sending the request?
    auto asyncOperation = RET_F_UNLESS(logger, il2cpp_utils::RunMethodUnsafe(webRequest, "SendWebRequest").value_or(nullptr));
    auto field = RET_F_UNLESS(logger, il2cpp_utils::FindField(asyncOperation, "m_completeCallback"));
    auto action = RET_F_UNLESS(logger, il2cpp_utils::MakeDelegate(field, completeWrapper, audioClipLoaded));
    if (!il2cpp_utils::SetFieldValue(asyncOperation, field, action))
    {
        return false;
    }
    logger.info("Began loading audio clip!");
    audioClips[path] = {false, nullptr};
    return true;
}
