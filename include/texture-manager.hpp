#pragma once
#include "asm/types.h"
#include <map>
#include <string>
#include <optional>
#include "../extern/beatsaber-hook/shared/utils/typedefs.h"

typedef struct texture_complete {
    std::string_view path;
    Il2CppObject* webRequest;
} texture_complete_t;

typedef struct texture_pair {
    bool loaded;
    Il2CppObject* texture;
} texture_pair_t;

class TextureManager {
    public:
        void Initialize(std::vector<std::string>& paths);
        bool LoadTexture(std::string_view path);
        std::optional<Il2CppObject*> GetTexture(std::string_view path);
    private:
        static std::map<std::string, texture_pair_t> textures;
        static void textureLoaded(texture_complete_t* completeWrapper);
};