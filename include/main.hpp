#pragma once
#include <dlfcn.h>
#include "../../beatsaber-hook/shared/utils/utils.h"
#include "../../beatsaber-hook/shared/customui/customui.hpp"
#include "utils.hpp"

class segment;

static std::optional<segment> getBestSegment(std::vector<segment>& segments, int comparison);
void checkjudgments(Il2CppObject* flyingScoreEffect, int beforeCut, int afterCut, int cutDistance);
void setConfigToCurrentSeason();
void loadConfig();

MAKE_HOOK_OFFSETLESS(FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent, void, Il2CppObject* self, Il2CppObject* saberSwingRatingCounter, float rating) {
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    auto noteCutInfo = il2cpp_utils::GetFieldValueUnsafe<Il2CppObject*>(self, "_noteCutInfo");
    static auto rawScoreWithoutMultiplier = il2cpp_utils::FindMethod("", "ScoreController", "RawScoreWithoutMultiplier", 4);
    il2cpp_utils::RunMethod(nullptr, rawScoreWithoutMultiplier, noteCutInfo, &beforeCut, &afterCut, &cutDistance);
    checkjudgments(self, beforeCut, afterCut, cutDistance);
}

MAKE_HOOK_OFFSETLESS(FlyingScoreEffect_InitAndPresent, void, Il2CppObject* self, Il2CppObject* noteCutInfo, int multiplier, float duration, Vector3 targetPos, Quaternion rotation, Color color) {

}

extern "C" void load();
