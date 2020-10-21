#include "utils.hpp"
#include "HSV.hpp"
#include "extern/beatsaber-hook/shared/utils/utils.h"
#include "extern/beatsaber-hook/shared/utils/typedefs.h"
#include "extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"

// FlyingScoreEffect::HandleSaberSwingRatingCounterDidChangeEvent(SaberSwingRatingCounter, float)
MAKE_HOOK_OFFSETLESS(FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent, void, Il2CppObject* self, Il2CppObject* saberSwingRatingCounter, float rating) {
    FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent(self, saberSwingRatingCounter, rating);
    HSV::HandleSaberSwingRatingCounterChangeEvent(self);
}

// FlyingScoreEffect::InitAndPresent(NoteCutInfo, int, float, Vector3, Quaternion, Color)
MAKE_HOOK_OFFSETLESS(FlyingScoreEffect_InitAndPresent, void, Il2CppObject* self, Il2CppObject* noteCutInfo, int multiplier, float duration, Vector3 targetPos, Quaternion rotation, Color color) {
    HSV::InitAndPresent_Prefix(self, targetPos, duration);
    FlyingScoreEffect_InitAndPresent(self, noteCutInfo, multiplier, duration, targetPos, rotation, color);
    HSV::InitAndPresent_Postfix(self, noteCutInfo);
}

// FlyingScoreSpawner::HandleFlyingScoreEffectDidFinish(FlyingScoreEffect)
MAKE_HOOK_OFFSETLESS(FlyingScoreSpawner_HandleFlyingScoreEffectDidFinish, void, Il2CppObject* self, Il2CppObject* flyingObjectEffect) {
    FlyingScoreSpawner_HandleFlyingScoreEffectDidFinish(self, flyingObjectEffect);
    HSV::effectDidFinish(flyingObjectEffect);
}

// BeatmapObjectExecutionRatingsRecorder/CutScoreHandler::HandleSwingRatingCounterDidFinishEvent(SaberSwingRatingCounter)
MAKE_HOOK_OFFSETLESS(CutScoreHandler_HandleSwingRatingCounterDidFinishEvent, void, Il2CppObject* self, Il2CppObject* counter) {
    CutScoreHandler_HandleSwingRatingCounterDidFinishEvent(self, counter);
    HSV::judge(counter);
}

// VRUIControls.VRPointer::Process(PointerEventData)
MAKE_HOOK_OFFSETLESS(VRUIControls_VRPointer_Process, void, Il2CppObject* self, Il2CppObject* pointerEventData) {
    VRUIControls_VRPointer_Process(self, pointerEventData);
    HSV::Notification_Update();
}

// MainMenuViewController::DidActivate(bool, ViewController.ActivationType)
MAKE_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, void, Il2CppObject* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    HSV::Notification_Init(self);
    HSV::Notification_Create();
}

// MainMenuViewController::HandleMenuButton(MainMenuViewController.MenuButton)
MAKE_HOOK_OFFSETLESS(MainMenuViewController_HandleMenuButton, void, Il2CppObject* self, int menuButton) {
    HSV::Notification_Invalid();
    MainMenuViewController_HandleMenuButton(self, menuButton);
}

// TODO: Add scene transition hooks to clear/ensure destruction of notification
// TODO: Add hooks on game start to async load the images and audio that would be needed

// UnityEngine.SceneManagement::SceneManager::Internal_ActiveSceneChanged(Scene, Scene)
MAKE_HOOK_OFFSETLESS(SceneManager_Internal_ActiveSceneChanged, void, Scene oldScene, Scene newScene) {
    SceneManager_Internal_ActiveSceneChanged(oldScene, newScene);
    HSV::SceneLoaded(newScene);
}

// Install hooks
extern "C" void load() {
    #ifdef SILENT
    Logger::disable();
    #endif
    HSV::loadConfig();
    getLogger().info("Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent, il2cpp_utils::FindMethodUnsafe("", "FlyingScoreEffect", "HandleSaberSwingRatingCounterDidChangeEvent", 2));
    INSTALL_HOOK_OFFSETLESS(FlyingScoreEffect_InitAndPresent, il2cpp_utils::FindMethodUnsafe("", "FlyingScoreEffect", "InitAndPresent", 6));
    INSTALL_HOOK_OFFSETLESS(FlyingScoreSpawner_HandleFlyingScoreEffectDidFinish, il2cpp_utils::FindMethodUnsafe("", "FlyingScoreSpawner", "HandleFlyingScoreEffectDidFinish", 1));
    INSTALL_HOOK_OFFSETLESS(CutScoreHandler_HandleSwingRatingCounterDidFinishEvent, il2cpp_utils::FindMethodUnsafe("", "BeatmapObjectExecutionRatingsRecorder/CutScoreHandler", "HandleSwingRatingCounterDidFinish", 1));
    INSTALL_HOOK_OFFSETLESS(VRUIControls_VRPointer_Process, il2cpp_utils::FindMethodUnsafe("VRUIControls", "VRPointer", "Process", 1));
    INSTALL_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 3));
    INSTALL_HOOK_OFFSETLESS(MainMenuViewController_HandleMenuButton, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "HandleMenuButton", 1));
    INSTALL_HOOK_OFFSETLESS(SceneManager_Internal_ActiveSceneChanged, il2cpp_utils::FindMethodUnsafe("UnityEngine.SceneManagement", "SceneManager", "Internal_ActiveSceneChanged", 2));
    getLogger().info("Installed hooks!");
}
