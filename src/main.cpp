#include "beatsaber-hook/shared/utils/logging.hpp"
#include "modloader/shared/modloader.hpp"
#include "config.hpp"
#include "audio-manager.hpp"
#include "sprite-manager.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "HSV.hpp"
#ifdef NOTIFICATION
#include "notification.h"
NotificationBox HSV::notification;
#endif

HSVConfig HSV::config;
AudioManager HSV::audioManager;
SpriteManager HSV::spriteManager;
bool HSV::configValid = false;
Il2CppObject* HSV::currentEffect;
std::map<Il2CppObject*, swingRatingCounter_context> HSV::swingRatingMap;
static ModInfo modInfo;

const ModInfo& getModInfo() {
    return modInfo;
}

Logger& logger() {
    static auto logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

Configuration& getConfig() {
    static Configuration overall_config(modInfo);
    return overall_config;
}

extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
    logger().info("Calling setup!");
}
