#pragma once

#include "audio-manager.hpp"
#include "config.hpp"
#include "sprite-manager.hpp"
#include <optional>
#ifdef NOTIFICATION
#include "notification.h"
#endif

struct Il2CppObject;

// Holds information to be used on BeatmapObjectExecutionRatingsRecorder.HandleSwingRatingCounterDidFinishEvent
struct swingRatingCounter_context {
    Il2CppObject* noteCutInfo;
    Il2CppObject* flyingScoreEffect;
};

class HSV {
    public:
    static HSVConfig config;
    static AudioManager audioManager;
    static SpriteManager spriteManager;
    #ifdef NOTIFICATION
    static NotificationBox notification;
    #endif
    static bool configValid;
    static Il2CppObject* currentEffect;
    static std::map<Il2CppObject*, swingRatingCounter_context> swingRatingMap;

    // Notification methods
    static void PushNotification(std::string_view str);
    static void Notification_Update();
    static void Notification_Init(Il2CppObject* parent);
    static bool Notification_Create();
    static void Notification_Invalid();

    // Configuration methods
    static void setConfigToCurrentSeason();
    static void loadConfig();

    // Judgment methods
    static void checkJudgments(Il2CppObject* flyingScoreEffect, int beforeCut, int afterCut, int cutDistance);
    static void effectDidFinish(Il2CppObject* flyingObjectEffect);
    static void judge(Il2CppObject* counter);
    static void judgeNoContext(Il2CppObject* flyingScoreEffect, Il2CppObject* noteCutInfo);
    static std::optional<int> getBestJudgment(std::vector<judgment>& judgments, int comparison);
    static std::optional<const segment> getBestSegment(std::vector<segment>& segments, int comparison);
    static std::optional<Color> fadeBetween(judgment from, judgment to, int score, Color initialColor);
    static bool addColor(Il2CppObject* flyingScoreEffect, int bestIndex, int score);
    static bool addText(Il2CppObject* flyingScoreEffect, judgment best, int beforeCut, int afterCut, int cutDistance);
    static bool addImage(Il2CppObject* flyingScoreEffect, judgment best, int beforeCut, int afterCut, int cutDistance);
    static bool addAudio(Il2CppObject* textObj, judgment toPlay);
    static Il2CppString* parseFormattedText(judgment best, int beforeCut, int afterCut, int cutDistance);

    // Hook exposed methods
    static void HandleSaberSwingRatingCounterChangeEvent(Il2CppObject* self);
    static void InitAndPresent_Prefix(Il2CppObject* self, Vector3& targetPos, float& duration);
    static void InitAndPresent_Postfix(Il2CppObject* self, Il2CppObject* noteCutInfo);
    static void SceneLoaded(Scene scene);
};