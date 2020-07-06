#include <dlfcn.h>
#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include "../include/libs/modloader/modloader.hpp"
#include "../include/main.hpp"
#include "../include/config.hpp"
#include "../include/notification.h"
#include "../include/audio-manager.hpp"
#include "../include/sprite-manager.hpp"
#include <ctime>
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"
#include <sstream>
#include <strstream>

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

static HSVConfig config;
static AudioManager audioManager;
static SpriteManager spriteManager;
static NotificationBox notification;
static bool configValid = true;

#define HANDLE_CONFIG_FAILURE(condition) if (!condition) { \
    getLogger().error("Config failed to load properly! Pushing notification..."); \
    getLogger().error("Assertion caught in: %s %s.%d", __PRETTY_FUNCTION__, __FILE__, __LINE__); \
    configValid = false; \
    notification.pushNotification("Config failed to load properly! Please ensure your JSON was configured correctly!"); \
}

std::optional<int> getBestJudgment(std::vector<judgment>& judgments, int comparison) {
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
    getLogger().debug("bestIndex: %d", i);
    return i;
}

std::optional<segment> getBestSegment(std::vector<segment>& segments, int comparison) {
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

Il2CppString* parseFormattedText(judgment best, int beforeCut, int afterCut, int cutDistance) {
    std::stringstream ststr;
    getLogger().debug("%d, %d, %d", beforeCut, afterCut, cutDistance);
    bool isPercent = false;
    // TODO: Can make this EVEN FASTER by getting a list of indices of where the %'s are ONCE
    // Tokenize this, cache text locations AOT
    // And then replacing the corresponding indices with them as we iterate
    for (auto itr = best.text->begin(); itr != best.text->end(); ++itr) {
        auto current = *itr;
        if (isPercent) {
            // If the last character was a %
            std::string buffer;
            std::optional<segment> out;
            switch (current) {
                case 'b':
                    ststr << beforeCut;
                    break;
                case 'c':
                    ststr << cutDistance;
                    break;
                case 'a':
                    ststr << afterCut;
                    break;
                case 'B':
                    out = getBestSegment(config.beforeCutAngleJudgments, beforeCut);
                    break;
                case 'C':
                    out = getBestSegment(config.accuracyJudgments, cutDistance);
                    break;
                case 'A':
                    out = getBestSegment(config.afterCutAngleJudgments, afterCut);
                    break;
                case 's':
                    ststr << (beforeCut + afterCut + cutDistance);
                    break;
                case 'p':
                    ststr.precision(2);
                    ststr << std::fixed << (beforeCut + afterCut + cutDistance) / 115.0f * 100.0;
                    break;
                case 'n':
                    ststr << "\n";
                    break;
                case '%':
                default:
                    ststr << "%%" << current;
            }
            if (out) {
                ststr << *(out->text);
            }
            isPercent = false;
            continue;
        }
        if (current == '%' && !isPercent) {
            isPercent = true;
        } else {
            ststr.put(current);
        }
    }
    return il2cpp_utils::createcsstr(ststr.str(), false);
}

std::optional<Color> fadeBetween(judgment from, judgment to, int score, Color initialColor) {
    auto reverseLerp = RET_NULLOPT_UNLESS(il2cpp_utils::RunMethod<float>("UnityEngine", "Mathf", "InverseLerp", (float)from.threshold, (float)to.threshold, (float)score));
    auto fadeToColor = RET_NULLOPT_UNLESS(to.color);
    return RET_NULLOPT_UNLESS(il2cpp_utils::RunMethod<Color>("UnityEngine", "Color", "Lerp", initialColor, fadeToColor, reverseLerp));
}

bool addColor(Il2CppObject* flyingScoreEffect, int bestIndex, int score) {
    getLogger().debug("Adding color for bestIndex: %d, score: %d", bestIndex, score);
    std::optional<Color> color = config.judgments[bestIndex].color;
    if (config.judgments[bestIndex].fade.value_or(false) && bestIndex != 0 && color) {
        color = fadeBetween(config.judgments[bestIndex], config.judgments[bestIndex - 1], score, *color);
    }

    if (color) {
        RET_F_UNLESS(il2cpp_utils::SetFieldValue(flyingScoreEffect, "_color", *color));
    } else {
        // Use default color of white (instead of whatever the previous color was)
        RET_F_UNLESS(il2cpp_utils::SetFieldValue(flyingScoreEffect, "_color", (Color){1.0f, 1.0f, 1.0f, 1.0f}));
    }
    return true;
}

bool addText(Il2CppObject* flyingScoreEffect, judgment best, int beforeCut, int afterCut, int cutDistance) {
    if (!best.text && !requires_text(config.displayMode)) {
        // Don't load any customized text if there is no need to
        // ex: imageOnly, no text provided
        return true;
    }
    Il2CppObject* text = RET_F_UNLESS(il2cpp_utils::GetFieldValue(flyingScoreEffect, "_text").value_or(nullptr));

    Il2CppString* judgment_cs = nullptr;
    if (config.displayMode == DISPLAY_MODE_FORMAT) {
        RET_F_UNLESS(best.text);
        judgment_cs = parseFormattedText(best, beforeCut, afterCut, cutDistance);
    } else if (config.displayMode == DISPLAY_MODE_NUMERIC) {
        RET_F_UNLESS(best.text);
        // Numeric display ONLY
        judgment_cs = RET_F_UNLESS(il2cpp_utils::GetPropertyValue<Il2CppString*>(text, "text"));
    } else if (config.displayMode == DISPLAY_MODE_SCOREONTOP) {
        RET_F_UNLESS(best.text);
        // Score on top
        // Add newline
        judgment_cs = RET_F_UNLESS(il2cpp_utils::GetPropertyValue<Il2CppString*>(text, "text"));
        // Faster to convert the old text, use c++ strings, convert it back than it is to use C# string.Concat twice (with two created C# strings)
        judgment_cs = il2cpp_utils::createcsstr(to_utf8(csstrtostr(judgment_cs)) + "\n" + *best.text);
    } else if (config.displayMode == DISPLAY_MODE_TEXTONLY) {
        // Will not display images, use formatted display
        RET_F_UNLESS(best.text);
        judgment_cs = parseFormattedText(best, beforeCut, afterCut, cutDistance);
    } else if (config.displayMode == DISPLAY_MODE_TEXTONTOP) {
        // Text on top
        judgment_cs = RET_F_UNLESS(il2cpp_utils::GetPropertyValue<Il2CppString*>(text, "text"));
        // Faster to convert the old text, use c++ strings, convert it back then it is to use C# string.Concat (although only marginally)
        judgment_cs = il2cpp_utils::createcsstr(*best.text + "\n" + to_utf8(csstrtostr(judgment_cs)));
    }
    else if (config.displayMode == DISPLAY_MODE_IMAGEONLY) {
        // Skip
        return true;
    } else if (config.displayMode == DISPLAY_MODE_IMAGEANDTEXT) {
        RET_F_UNLESS(best.text);
        judgment_cs = parseFormattedText(best, beforeCut, afterCut, cutDistance);
    }

    // Runtime invoke set_richText to true
    RET_F_UNLESS(il2cpp_utils::SetPropertyValue(text, "richText", true));

    // Runtime invoke set_enableWordWrapping false
    RET_F_UNLESS(il2cpp_utils::SetPropertyValue(text, "enableWordWrapping", false));

    // Runtime invoke set_overflowMode to OverflowModes.Overflow (0)
    RET_F_UNLESS(il2cpp_utils::SetPropertyValue(text, "overflowMode", 0));

    // Set text if it is not null
    RET_F_UNLESS(judgment_cs);
    RET_F_UNLESS(il2cpp_utils::SetPropertyValue(text, "text", judgment_cs));
    getLogger().debug("Using text: %s", best.text->data());
    return true;
}

bool addImage(Il2CppObject* flyingScoreEffect, judgment best, int beforeCut, int afterCut, int cutDistance) {
    getLogger().debug("Adding image...");
    if (config.displayMode == DISPLAY_MODE_IMAGEONLY) {
        RET_F_UNLESS(best.imagePath);
    } else if (config.displayMode == DISPLAY_MODE_IMAGEANDTEXT) {
        if (!best.imagePath) {
            // Simply use fallback text if no image is provided
            return true;
        }
    } else {
        // Don't display an image
        return true;
    }
    static auto spriteRendererType = il2cpp_utils::GetSystemType("UnityEngine", "SpriteRenderer");
    RET_F_UNLESS(spriteRendererType);
    Il2CppObject* existing = RET_F_UNLESS(il2cpp_utils::RunMethod(flyingScoreEffect, "GetComponent", spriteRendererType));
    if (existing) {
        // Already displaying an image, no need to fail
        getLogger().debug("found sprite renderer: %p", existing);
    } else {
        // SpriteRenderer spriteRender = flyingScoreEffect.gameObject.AddComponent(typeof(SpriteRenderer));
        auto go = RET_F_UNLESS(il2cpp_utils::GetPropertyValue(flyingScoreEffect, "gameObject").value_or(nullptr));
        existing = RET_F_UNLESS(il2cpp_utils::RunMethod(go, "AddComponent", spriteRendererType).value_or(nullptr));
        getLogger().debug("Created sprite renderer: %p", existing);
    }
    // Get texture
    auto sprite = spriteManager.GetSprite(*best.imagePath).value_or(nullptr);
    if (sprite) {
        getLogger().debug("Found sprite!");
        // spriteRenderer.set_sprite(sprite);
        RET_F_UNLESS(il2cpp_utils::SetPropertyValue(existing, "sprite", sprite));
        getLogger().debug("Set sprite!");
        if (best.color) {
            // spriteRenderer.set_color(color);
            RET_F_UNLESS(il2cpp_utils::SetPropertyValue(existing, "color", *best.color));
        } else {
            // Use default color instead of last color
            RET_F_UNLESS(il2cpp_utils::SetPropertyValue(existing, "color", (Color){1.0f, 1.0f, 1.0f, 1.0f}));
        }
    }
    getLogger().debug("Adding image complete!");
    // TODO: Add segment images here
    return true;
}

bool addAudio(Il2CppObject* textObj, judgment toPlay) {
    // Check to see if we have an AudioSource already.
    // If we do, that means we already started our audio, so don't make another
    // If we don't make one and play audio on it.
    if (!toPlay.soundPath) {
        // No need to fail with logs if we didn't even want to add a sound
        return true;
    }
    static auto audioSourceType = il2cpp_utils::GetSystemType("UnityEngine", "AudioSource");
    RET_F_UNLESS(audioSourceType);
    Il2CppObject* existing = RET_F_UNLESS(il2cpp_utils::RunMethod(textObj, "GetComponent", audioSourceType));
    if (existing) {
        // Already playing a sound, no need to fail
        getLogger().debug("Existing AudioSource: %p", existing);
    } else {
        auto go = RET_F_UNLESS(il2cpp_utils::GetPropertyValue(textObj, "gameObject").value_or(nullptr));
        existing = RET_F_UNLESS(il2cpp_utils::RunMethod(go, "AddComponent", audioSourceType).value_or(nullptr));
        getLogger().debug("Created AudioSource: %p", existing);
    }
    // Get audio clip
    auto clip = audioManager.GetAudioClip(*toPlay.soundPath).value_or(nullptr);
    if (clip) {
        RET_F_UNLESS(il2cpp_utils::RunMethod(existing, "PlayOneShot", clip, toPlay.soundVolume.value_or(1.0f)));
    }
    return true;
}

void checkJudgments(Il2CppObject* flyingScoreEffect, int beforeCut, int afterCut, int cutDistance) {
    getLogger().debug("Checking judgments!");
    if (!configValid) {
        return;
    }
    auto bestIndex = getBestJudgment(config.judgments, beforeCut + afterCut + cutDistance);
    RET_V_UNLESS(bestIndex);
    getLogger().debug("Index: %d", *bestIndex);
    auto best = config.judgments[*bestIndex];

    getLogger().debug("Adding color");
    if (!addColor(flyingScoreEffect, *bestIndex, beforeCut + afterCut + cutDistance)) {
        getLogger().error("Failed to add color!");
    }

    getLogger().debug("Adding image");
    if (!addImage(flyingScoreEffect, best, beforeCut, afterCut, cutDistance)) {
        getLogger().error("Failed to add image!");
    }

    getLogger().debug("Adding text");
    if (!addText(flyingScoreEffect, best, beforeCut, afterCut, cutDistance)) {
        getLogger().error("Failed to add text!");
    }

    getLogger().debug("Adding sound");
    if (!addAudio(flyingScoreEffect, best)) {
        getLogger().error("Failed to add audio!");
    }
    getLogger().debug("Complete with judging!");
}
// Checks season, sets config to correct season
void setConfigToCurrentSeason() {
    static std::string configBackupPath = string_format(CONFIG_PATH_FORMAT, Modloader::getApplicationId()) + MOD_ID + "_backup.json";
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
                    getLogger().debug("Restoring config from: %s", configBackupPath);
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

void loadConfig() {
    getLogger().info("Loading Configuration...");
    getConfig().Load();
    HANDLE_CONFIG_FAILURE(ConfigHelper::LoadConfig(config, getConfig().config));
    if (config.VersionLessThanEqual(2, 4, 0) || config.type == CONFIG_TYPE_CHRISTMAS) {
        // Let's just auto fix everyone's configs that are less than or equal to 2.4.0 or are of Christmas type
        getLogger().debug("Setting to default because version <= 2.4.0! Actual: %i.%i.%i", config.majorVersion, config.minorVersion, config.patchVersion);
        config.SetToDefault();
        config.WriteToConfig(getConfig().config);
        configValid = true;
    }
    getLogger().info("Loaded Configuration! Metadata: type: %i, useSeasonalThemes: %c, restoreAfterSeason: %c", config.type, config.useSeasonalThemes ? 't' : 'f', config.restoreAfterSeason ? 't' : 'f');
    setConfigToCurrentSeason();
    getLogger().info("Set Configuration to current season! Type: %i", config.type);
}

static Il2CppObject* currentEffect;
static std::map<Il2CppObject*, swingRatingCounter_context_t> swingRatingMap;

// Called during: FlyingObjectEffect.didFinishEvent
// FlyingScoreEffect.HandleFlyingScoreEffectDidFinish
void effectDidFinish(Il2CppObject* flyingObjectEffect) {
    if (flyingObjectEffect == currentEffect) {
        currentEffect = nullptr;
    }
}

void judgeNoContext(Il2CppObject* flyingScoreEffect, Il2CppObject* noteCutInfo) {
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    RET_V_UNLESS(il2cpp_utils::RunMethod("", "ScoreModel", "RawScoreWithoutMultiplier", noteCutInfo, beforeCut, afterCut, cutDistance));
    checkJudgments(flyingScoreEffect, beforeCut, afterCut, cutDistance);
}

void judge(Il2CppObject* counter) {
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
            checkJudgments(context.flyingScoreEffect, beforeCut, afterCut, cutDistance);
        }
    }
}

void HandleSaberSwingRatingCounterChangeEvent(Il2CppObject* self) {
    if (config.doIntermediateUpdates) {
        auto noteCutInfo = RET_V_UNLESS(il2cpp_utils::GetFieldValue(self, "_noteCutInfo").value_or(nullptr));
        judgeNoContext(self, noteCutInfo);
    }
}

void InitAndPresent_Prefix(Il2CppObject* self, Vector3& targetPos, float& duration) {
    if (config.useFixedPos) {
        targetPos.x = config.fixedPosX;
        targetPos.y = config.fixedPosY;
        targetPos.z = config.fixedPosZ;
        auto transform = RET_V_UNLESS(il2cpp_utils::GetPropertyValue(self, "transform").value_or(nullptr));
        RET_V_UNLESS(il2cpp_utils::SetPropertyValue(self, "position", targetPos));

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
}

void InitAndPresent_Postfix(Il2CppObject* self, Il2CppObject* noteCutInfo) {
    judgeNoContext(self, noteCutInfo);
    if (!config.doIntermediateUpdates) {
        // Set the duration back to the default, which is 0.7 seconds
        RET_V_UNLESS(il2cpp_utils::SetFieldValue(self, "_duration", 0.7f));
    }
    auto counter = RET_V_UNLESS(il2cpp_utils::GetPropertyValue(noteCutInfo, "swingRatingCounter").value_or(nullptr));
    swingRatingMap[counter] = {noteCutInfo, self};
    getLogger().debug("Complete with InitAndPresent!");
}

void Notification_Init(Il2CppObject* parent) {
    getLogger().debug("Initialized notificationBox, parent: %p", parent);
    notification.notificationBox.fontSize = 5;
    notification.notificationBox.anchoredPosition = {0.0f, -100.0f};
    notification.notificationBox.parentTransform = parent;
}

bool Notification_Create() {
    return notification.create();
}

void Notification_Update() {
    notification.parallelUpdate();
}

void Notification_Invalid() {
    notification.markInvalid();
}

void SceneLoaded(Scene scene) {
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

// FlyingScoreEffect::HandleSaberSwingRatingCounterDidChangeEvent(SaberSwingRatingCounter, float)
MAKE_HOOK_OFFSETLESS(FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent, void, Il2CppObject* self, Il2CppObject* saberSwingRatingCounter, float rating) {
    FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent(self, saberSwingRatingCounter, rating);
    HandleSaberSwingRatingCounterChangeEvent(self);
}

// FlyingScoreEffect::InitAndPresent(NoteCutInfo, int, float, Vector3, Quaternion, Color)
MAKE_HOOK_OFFSETLESS(FlyingScoreEffect_InitAndPresent, void, Il2CppObject* self, Il2CppObject* noteCutInfo, int multiplier, float duration, Vector3 targetPos, Quaternion rotation, Color color) {
    InitAndPresent_Prefix(self, targetPos, duration);
    FlyingScoreEffect_InitAndPresent(self, noteCutInfo, multiplier, duration, targetPos, rotation, color);
    InitAndPresent_Postfix(self, noteCutInfo);
}

// FlyingScoreSpawner::HandleFlyingScoreEffectDidFinish(FlyingScoreEffect)
MAKE_HOOK_OFFSETLESS(FlyingScoreSpawner_HandleFlyingScoreEffectDidFinish, void, Il2CppObject* self, Il2CppObject* flyingObjectEffect) {
    FlyingScoreSpawner_HandleFlyingScoreEffectDidFinish(self, flyingObjectEffect);
    effectDidFinish(flyingObjectEffect);
}

// BeatmapObjectExecutionRatingsRecorder/CutScoreHandler::HandleSwingRatingCounterDidFinishEvent(SaberSwingRatingCounter)
MAKE_HOOK_OFFSETLESS(CutScoreHandler_HandleSwingRatingCounterDidFinishEvent, void, Il2CppObject* self, Il2CppObject* counter) {
    CutScoreHandler_HandleSwingRatingCounterDidFinishEvent(self, counter);
    judge(counter);
}

// VRUIControls.VRPointer::Process(PointerEventData)
MAKE_HOOK_OFFSETLESS(VRUIControls_VRPointer_Process, void, Il2CppObject* self, Il2CppObject* pointerEventData) {
    VRUIControls_VRPointer_Process(self, pointerEventData);
    Notification_Update();
}

// MainMenuViewController::DidActivate(bool, ViewController.ActivationType)
MAKE_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, void, Il2CppObject* self, bool firstActivation, int activationType) {
    MainMenuViewController_DidActivate(self, firstActivation, activationType);
    Notification_Init(self);
    Notification_Create();
}

// MainMenuViewController::HandleMenuButton(MainMenuViewController.MenuButton)
MAKE_HOOK_OFFSETLESS(MainMenuViewController_HandleMenuButton, void, Il2CppObject* self, int menuButton) {
    Notification_Invalid();
    MainMenuViewController_HandleMenuButton(self, menuButton);
}

// TODO: Add scene transition hooks to clear/ensure destruction of notification
// TODO: Add hooks on game start to async load the images and audio that would be needed

// UnityEngine.SceneManagement::SceneManager::Internal_ActiveSceneChanged(Scene, Scene)
MAKE_HOOK_OFFSETLESS(SceneManager_Internal_ActiveSceneChanged, void, Scene oldScene, Scene newScene) {
    SceneManager_Internal_ActiveSceneChanged(oldScene, newScene);
    SceneLoaded(newScene);
}

extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
    getLogger().info("Calling setup!");
}

// Install hooks
extern "C" void load() {
    loadConfig();
    getLogger().info("Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent, il2cpp_utils::FindMethodUnsafe("", "FlyingScoreEffect", "HandleSaberSwingRatingCounterDidChangeEvent", 2));
    INSTALL_HOOK_OFFSETLESS(FlyingScoreEffect_InitAndPresent, il2cpp_utils::FindMethodUnsafe("", "FlyingScoreEffect", "InitAndPresent", 6));
    INSTALL_HOOK_OFFSETLESS(FlyingScoreSpawner_HandleFlyingScoreEffectDidFinish, il2cpp_utils::FindMethodUnsafe("", "FlyingScoreSpawner", "HandleFlyingScoreEffectDidFinish", 1));
    INSTALL_HOOK_OFFSETLESS(CutScoreHandler_HandleSwingRatingCounterDidFinishEvent, il2cpp_utils::FindMethodUnsafe("", "BeatmapObjectExecutionRatingsRecorder/CutScoreHandler", "HandleSwingRatingCounterDidFinishEvent", 1));
    INSTALL_HOOK_OFFSETLESS(VRUIControls_VRPointer_Process, il2cpp_utils::FindMethodUnsafe("VRUIControls", "VRPointer", "Process", 1));
    INSTALL_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 2));
    INSTALL_HOOK_OFFSETLESS(MainMenuViewController_HandleMenuButton, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "HandleMenuButton", 1));
    INSTALL_HOOK_OFFSETLESS(SceneManager_Internal_ActiveSceneChanged, il2cpp_utils::FindMethodUnsafe("UnityEngine.SceneManagement", "SceneManager", "Internal_ActiveSceneChanged", 2));
    getLogger().info("Installed hooks!");
}