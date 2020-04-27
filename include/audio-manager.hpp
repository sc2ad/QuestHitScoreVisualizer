#pragma once
#include "asm/types.h"
#include <map>
#include <unordered_map>
#include <string>
#include <optional>
#include "../extern/beatsaber-hook/shared/utils/typedefs.h"

class HSVConfig;

typedef struct audio_complete {
    std::string path;
    Il2CppObject* webRequest;
} audio_complete_t;

typedef struct clip_pair {
    bool loaded;
    Il2CppObject* clip;
} clip_pair_t;

class AudioManager {
    public:
        void Initialize(HSVConfig config);
        void Clear();
        bool LoadAudioClip(std::string path);
        std::optional<Il2CppObject*> GetAudioClip(std::string path);
    private:
        static std::unordered_map<std::string, clip_pair_t> audioClips;
        int getAudioType(std::string path);
        static void audioClipLoaded(audio_complete_t* completeWrapper);
};