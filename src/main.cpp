#include <dlfcn.h>
#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include "../extern/beatsaber-hook/include/modloader.hpp"
#include "../include/config.hpp"
#include "../include/notification.h"
#include "../include/audio-manager.hpp"
#include "../include/sprite-manager.hpp"
#include <ctime>
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"
#include <sstream>
#include <strstream>
#include "HSV.hpp"

HSVConfig HSV::config;
AudioManager HSV::audioManager;
SpriteManager HSV::spriteManager;
NotificationBox HSV::notification;
bool HSV::configValid = false;
Il2CppObject* HSV::currentEffect;
std::map<Il2CppObject*, swingRatingCounter_context> HSV::swingRatingMap;
static ModInfo modInfo;

const ModInfo& getModInfo() {
    return modInfo;
}

const Logger& getLogger() {
    static const Logger& logger(modInfo);
    return logger;
}

Configuration& getConfig() {
    static Configuration overall_config(modInfo);
    return overall_config;
}

extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
    getLogger().info("Calling setup!");
}
