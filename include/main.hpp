#pragma once
#include <dlfcn.h>
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "notification.h"

// Holds information to be used on BeatmapObjectExecutionRatingsRecorder.HandleSwingRatingCounterDidFinishEvent
typedef struct swingRatingCounter_context {
    Il2CppObject* noteCutInfo;
    Il2CppObject* flyingScoreEffect;
} swingRatingCounter_context_t;

void checkJudgments(Il2CppObject* flyingScoreEffect, int beforeCut, int afterCut, int cutDistance);
void setConfigToCurrentSeason();
void loadConfig();

void effectDidFinish(Il2CppObject* flyingObjectEffect);
void judge(Il2CppObject* counter);

void HandleSaberSwingRatingCounterChangeEvent(Il2CppObject* self);
void InitAndPresent_Prefix(Il2CppObject* self, Vector3& targetPos, float& duration);
void InitAndPresent_Postfix(Il2CppObject* self, Il2CppObject* noteCutInfo);
void Notification_Init(Il2CppObject* parent);
bool Notification_Create();
void Notification_Update();
void Notification_Invalid();

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

extern "C" void load();
