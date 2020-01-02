#pragma once
#include "../../beatsaber-hook/shared/utils/utils.h"
#include "../../beatsaber-hook/shared/customui/customui.hpp"

static const MethodInfo* replace = nullptr;
static const MethodInfo* concat = nullptr;

static Il2CppString* replaceBuffer(Il2CppString* q, std::string_view left, std::string_view right);
static Il2CppString* concatBuffer(Il2CppString* left, std::string_view right);
static Il2CppString* concatBuffer(Il2CppString* left, Il2CppString* right);
static const char* getBestSegment(rapidjson::Value& segments, int comparison);
void checkJudgements(Il2CppObject* flyingScoreEffect, int beforeCut, int afterCut, int cutDistance);
void setConfigToCurrentSeason();
void loadConfig();

MAKE_HOOK_OFFSETLESS(FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent, void, Il2CppObject* self, Il2CppObject* saberSwingRatingCounter, float rating) {
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    auto noteCutInfo = il2cpp_utils::GetFieldValueUnsafe<Il2CppObject*>(self, "_noteCutInfo");
    static auto rawScoreWithoutMultiplier = il2cpp_utils::FindMethod("", "ScoreController", "RawScoreWithoutMultiplier", 4);
    il2cpp_utils::RunMethod(nullptr, rawScoreWithoutMultiplier, noteCutInfo, &beforeCut, &afterCut, &cutDistance);
    checkJudgements(self, beforeCut, afterCut, cutDistance);
}

extern "C" void load();
