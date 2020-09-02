#pragma once
#include "asm/types.h"
#include <map>
#include <unordered_map>
#include <string>
#include <optional>
#include "../extern/beatsaber-hook/shared/utils/typedefs.h"

class HSVConfig;

typedef struct texture_complete {
    std::string path;
    Il2CppObject* webRequest;
} texture_complete_t;

typedef struct sprite_pair {
    bool loaded;
    Il2CppObject* sprite;
} sprite_pair_t;

class SpriteManager {
    public:
        void Initialize(const HSVConfig& config);
        void Clear();
        bool LoadTexture(std::string path);
        std::optional<Il2CppObject*> GetSprite(std::string path);
        std::vector<std::string> spritePaths;
    private:
        static std::unordered_map<std::string, sprite_pair_t> sprites;
        static void textureLoaded(texture_complete_t* completeWrapper);
};