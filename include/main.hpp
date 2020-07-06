#pragma once

typedef struct Il2CppObject Il2CppObject;

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
