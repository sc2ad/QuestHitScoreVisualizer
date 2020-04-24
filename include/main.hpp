#pragma once
#include <dlfcn.h>
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "notification.h"

typedef struct effect_context {
    Il2CppObject* actionToRemove;
} effect_context_t;

typedef struct swingRatingCounter_context {
    Il2CppObject* actionToRemove;
    Il2CppObject* noteCutInfo;
    Il2CppObject* flyingScoreEffect;
} swingRatingCounter_context_t;

void checkJudgments(Il2CppObject* flyingScoreEffect, int beforeCut, int afterCut, int cutDistance);
void setConfigToCurrentSeason();
void loadConfig();
void HandleSaberSwingRatingCounterChangeEvent(Il2CppObject* self);
void InitAndPresent_Prefix(Il2CppObject* self, Vector3& targetPos);
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
    InitAndPresent_Prefix(self, targetPos);
    FlyingScoreEffect_InitAndPresent(self, noteCutInfo, multiplier, duration, targetPos, rotation, color);
    InitAndPresent_Postfix(self, noteCutInfo);
}

// VRUIControllers.VRPointer::Process(PointerEventData)
MAKE_HOOK_OFFSETLESS(VRUIControllers_VRPointer_Process, void, Il2CppObject* self, Il2CppObject* pointerEventData) {
    VRUIControllers_VRPointer_Process(self, pointerEventData);
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

extern "C" void load();
