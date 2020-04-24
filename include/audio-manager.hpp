#pragma once
#include "asm/types.h"
#include <map>
#include <string>
#include <optional>
#include "../extern/beatsaber-hook/shared/utils/typedefs.h"

typedef struct audio_complete {
    std::string_view path;
    Il2CppObject* webRequest;
} audio_complete_t;

typedef struct clip_pair {
    bool loaded;
    Il2CppObject* clip;
} clip_pair_t;

class AudioManager {
    public:
        void Initialize(std::vector<std::string>& paths);
        bool LoadAudioClip(std::string_view path);
        std::optional<Il2CppObject*> GetAudioClip(std::string_view path);
    private:
        static std::map<std::string, clip_pair_t> loadedAudioClips;
        int getAudioType(std::string_view path);
        static void audioClipLoaded(audio_complete_t* completeWrapper);
};