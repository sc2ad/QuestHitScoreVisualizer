#include "HSV.hpp"
#include "utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#ifndef RELEASE_BUILD
// Handle a config failure within the HSV class
#define HANDLE_CONFIG_FAILURE(condition) do { \
    if (!condition) { \
        getLogger().error("Config failed to load properly! Pushing notification..."); \
        getLogger().error("Assertion caught in: %s %s.%d", __PRETTY_FUNCTION__, __FILE__, __LINE__); \
        configValid = false; \
        HSV::PushNotification("Config failed to load properly! Please ensure your JSON was configured correctly!"); \
    } else { \
        configValid = true; \
    } \
} while(0)
#else
// Handle a config failure within the HSV class
#define HANDLE_CONFIG_FAILURE(condition) do { \
    if (!condition) { \
        getLogger().error("Config failed to load properly! Pushing notification..."); \
        configValid = false; \
        HSV::PushNotification("Config failed to load properly! Please ensure your JSON was configured correctly!"); \
    } else { \
        configValid = true; \
    } \
} while(0)
#endif

void HSV::Notification_Init(Il2CppObject* parent) {
    #ifdef NOTIFICATION
    getLogger().debug("Initialized notificationBox, parent: %p", parent);
    notification.notificationBox.fontSize = 5;
    notification.notificationBox.anchoredPosition = {0.0f, -100.0f};
    notification.notificationBox.parentTransform = parent;
    #endif
}

bool HSV::Notification_Create() {
    #ifdef NOTIFICATION
    return notification.create();
    #else
    return false;
    #endif
}

void HSV::Notification_Update() {
    #ifdef NOTIFICATION
    notification.parallelUpdate();
    #endif
}

void HSV::Notification_Invalid() {
    #ifdef NOTIFICATION
    notification.markInvalid();
    #endif
}

void HSV::PushNotification(std::string_view str) {
    #ifdef NOTIFICATION
    notification.pushNotification(str);
    #endif
}

std::optional<int> HSV::getBestJudgment(std::vector<judgment>& judgments, int comparison) {
    static auto length = config.judgments.size();
    if (length == 0) {
        return std::nullopt;
    }
    int i;
    for (i = 0; i < length; i++) {
        if (comparison >= config.judgments[i].threshold) {
            break;
        }
    }
    return i;
}

std::optional<const segment> HSV::getBestSegment(std::vector<segment>& segments, int comparison) {
    auto size = segments.size();
    if (size == 0) {
        return std::nullopt;
    }
    auto& best = segments[0];
    for (int i = 1; i < size; i++) {
        if (comparison >= segments[i].threshold) {
            break;
        }
        best = segments[i];
    }
    return best;
}

// Called during: FlyingObjectEffect.didFinishEvent
// FlyingScoreEffect.HandleFlyingScoreEffectDidFinish
void HSV::effectDidFinish(Il2CppObject* flyingObjectEffect) {
    if (flyingObjectEffect == currentEffect) {
        currentEffect = nullptr;
    }
}

void HSV::judgeNoContext(Il2CppObject* flyingScoreEffect, Il2CppObject* noteCutInfo) {
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    RET_V_UNLESS(il2cpp_utils::RunMethod("", "ScoreModel", "RawScoreWithoutMultiplier", noteCutInfo, beforeCut, afterCut, cutDistance));
    checkJudgments(flyingScoreEffect, beforeCut, afterCut, cutDistance);
}

void HSV::judge(Il2CppObject* counter) {
    // Get FlyingScoreEffect and NoteCutInfo from map
    auto itr = swingRatingMap.find(counter);
    if (itr == swingRatingMap.end()) {
        getLogger().debug("counter: %p was not in swingRatingMap!", counter);
        return;
    }
    auto context = itr->second;
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;

    if (context.noteCutInfo) {
        RET_V_UNLESS(il2cpp_utils::RunMethod("", "ScoreModel", "RawScoreWithoutMultiplier", context.noteCutInfo, beforeCut, afterCut, cutDistance));
        if (context.flyingScoreEffect) {
            if (!config.showInitialScore) {
                // We need to explicitly re-enable the indicator (text is already properly set)
                auto* indicator = RET_V_UNLESS(il2cpp_utils::GetFieldValue(context.flyingScoreEffect, "_maxCutDistanceScoreIndicator"));
                RET_V_UNLESS(il2cpp_utils::SetPropertyValue(indicator, "enabled", true));
            }
            checkJudgments(context.flyingScoreEffect, beforeCut, afterCut, cutDistance);
        }
    }
}

void HSV::HandleSaberSwingRatingCounterChangeEvent(Il2CppObject* self) {
    if (config.doIntermediateUpdates) {
        auto noteCutInfo = RET_V_UNLESS(il2cpp_utils::GetFieldValue(self, "_noteCutInfo").value_or(nullptr));
        judgeNoContext(self, noteCutInfo);
    }
}

void HSV::InitAndPresent_Prefix(Il2CppObject* self, Vector3& targetPos, float& duration) {
    if (config.useFixedPos) {
        targetPos.x = config.fixedPosX;
        targetPos.y = config.fixedPosY;
        targetPos.z = config.fixedPosZ;
        auto transform = RET_V_UNLESS(il2cpp_utils::GetPropertyValue(self, "transform").value_or(nullptr));
        RET_V_UNLESS(il2cpp_utils::SetPropertyValue(transform, "position", targetPos));

        if (currentEffect) {
            // Disable the current effect
            RET_V_UNLESS(il2cpp_utils::SetFieldValue(currentEffect, "_duration", 0.0f));
        }
        currentEffect = self;
    } else if (!config.doIntermediateUpdates) {
        // If there are no intermediate updates, in order to remove the 'flickering' score, set the duration to 0 and fix it later
        // Duration being set to 0 would be wrong, since we would destroy before doing anything
        duration = 0.01f;
    }
    if (!config.showInitialScore) {
        duration = 0;
    }
}

void HSV::InitAndPresent_Postfix(Il2CppObject* self, Il2CppObject* noteCutInfo) {
    if (!config.doIntermediateUpdates || !config.showInitialScore) {
        // Set the duration back to the default, which is 0.7 seconds
        RET_V_UNLESS(il2cpp_utils::SetFieldValue(self, "_duration", 0.7f));
    }
    if (!config.showInitialScore) {
        // If we plan on hiding the original score until we have computed the end result, we simply set the duration
        // and set the text + underline to nothing.
        // We reenable these based off of our final score instead.
        auto* textObj = RET_V_UNLESS(il2cpp_utils::GetFieldValue(self, "_text"));
        static auto* emptyStr = il2cpp_utils::createcsstr("", il2cpp_utils::StringType::Permanent);
        RET_V_UNLESS(il2cpp_utils::SetPropertyValue(textObj, "text", emptyStr));
        auto* indicator = RET_V_UNLESS(il2cpp_utils::GetFieldValue(self, "_maxCutDistanceScoreIndicator"));
        RET_V_UNLESS(il2cpp_utils::SetPropertyValue(indicator, "enabled", false));
    }
    if (config.showInitialScore) {
        judgeNoContext(self, noteCutInfo);
    }
    auto counter = RET_V_UNLESS(il2cpp_utils::GetPropertyValue(noteCutInfo, "swingRatingCounter").value_or(nullptr));
    swingRatingMap[counter] = {noteCutInfo, self};
    getLogger().debug("Complete with InitAndPresent!");
}

void HSV::SceneLoaded(Scene scene) {
    static auto nameMethod = il2cpp_utils::FindMethod("UnityEngine.SceneManagement", "Scene", "get_name");
    auto name = RET_V_UNLESS(il2cpp_utils::RunMethod<Il2CppString*>(&scene, nameMethod).value_or(nullptr));
    auto convName = to_utf8(csstrtostr(name));
    getLogger().info("Loading scene: %s", convName.data());
    if (convName == "GameCore") {
        // TODO: Determine why Initialize crashes with segv to address in memcpy
        getLogger().info("Clearing loaded audio and sprites!");
        audioManager.Clear();
        audioManager.Initialize(config);
        spriteManager.Clear();
        spriteManager.Initialize(config);
    }
}

// Checks season, sets config to correct season
void HSV::setConfigToCurrentSeason() {
    static auto configBackupPath = Configuration::getConfigFilePath(ModInfo{std::string(MOD_ID) + "_backup", VERSION});
    if (config.useSeasonalThemes) {
        // Check season
        time_t now = std::time(nullptr);
        tm* currentTm = std::localtime(&now);
        getLogger().debug("Current datetime: (%i/%i)", currentTm->tm_mon, currentTm->tm_mday);
        // Christmas is 1 + 11 month, 23 - 25 day
        if (currentTm->tm_mon == 11 && (currentTm->tm_mday >= 23 && currentTm->tm_mday <= 24)) {
            if (config.backupBeforeSeason) {
                getLogger().debug("Backing up config before seasonal swap...");
                // Before we backup, we must first ensure we have written out the correct info
                // So we don't have to fail to parse it again in the future
                config.WriteToConfig(getConfig().config);
                ConfigHelper::BackupConfig(getConfig().config, configBackupPath);
            }
            getLogger().debug("Setting to Christmas config!");
            config.SetToSeason(CONFIG_TYPE_CHRISTMAS);
        } else {
            if (config.type != CONFIG_TYPE_STANDARD) {
                // Otherwise, set to standard - iff config.restoreAfterSeason is set and there is a viable backup
                if (config.restoreAfterSeason && fileexists(configBackupPath)) {
                    getLogger().debug("Restoring config from: %s", configBackupPath.c_str());
                    ConfigHelper::RestoreConfig(configBackupPath);
                    HANDLE_CONFIG_FAILURE(ConfigHelper::LoadConfig(config, getConfig().config));
                    // Delete the old path to ensure we don't load from it again
                    deletefile(configBackupPath);
                } else if (config.restoreAfterSeason) {
                    // If there isn't a viable backup, but we want to restore, set to default
                    getLogger().debug("Setting config to default from type: %i", config.type);
                    config.SetToDefault();
                }
            }
        }
        getLogger().debug("Writing Config to JSON file!");
        config.WriteToConfig(getConfig().config);
        getLogger().debug("Writing Config JSON to file!");
        getConfig().Write();
    }
}

void HSV::loadConfig() {
    getLogger().info("Loading Configuration...");
    getConfig().Load();
    HANDLE_CONFIG_FAILURE(ConfigHelper::LoadConfig(config, getConfig().config));
    if (!configValid && (config.VersionLessThanEqual(2, 4, 0) || config.type == CONFIG_TYPE_CHRISTMAS)) {
        // Let's just auto fix everyone's configs that are less than or equal to 2.4.0 or are of Christmas type
        // Even if they are invalid! This allows us to actually make the default config.
        getLogger().debug("Setting to default because version <= 2.4.0! Actual: %i.%i.%i", config.majorVersion, config.minorVersion, config.patchVersion);
        config.SetToDefault();
        config.WriteToConfig(getConfig().config);
        getConfig().Write();
        configValid = true;
    }
    if (!configValid && config.isDefaultConfig) {
        getLogger().debug("Setting to default because config failed to load, even though it was default config!");
        config.SetToDefault();
        config.WriteToConfig(getConfig().config);
        getConfig().Write();
        configValid = true;
    }
    if (configValid) {
        getLogger().info("Loaded Configuration! Metadata: type: %i, useSeasonalThemes: %c, restoreAfterSeason: %c", config.type, config.useSeasonalThemes ? 't' : 'f', config.restoreAfterSeason ? 't' : 'f');
        setConfigToCurrentSeason();
        getLogger().info("Set Configuration to current season! Type: %i", config.type);
    } else {
        getLogger().info("Configuration is invalid! Please ensure the version is >= 2.4.0 and the config is the correct format!");
    }
}
