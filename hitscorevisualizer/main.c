#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#include "../beatsaber-hook/shared/inline-hook/inlineHook.h"
#include "../beatsaber-hook/shared/utils/utils.h"

#undef log
#define log(...) __android_log_print(ANDROID_LOG_INFO, "QuestHook", "[HitScoreVisualizer] " __VA_ARGS__)

typedef struct judgement {
    int threshold;
    float r;
    float g;
    float b;
    float a;
    char* text;
} judgement_t;

judgement_t judgements[6];

typedef struct __attribute__((__packed__)) {
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct __attribute__((__packed__)) {
    float x;
    float y;
    float z;
} Vector3;

typedef struct __attribute__((__packed__)) {
    // First field begins at 0x58, could fill in useless
    // byte data here to just "take up space"
    char data[0x58];
    void* fadeAnimationCurve;
    void* maxCutDistanceScoreIndicator;
    void* text;
    Color color;
    float colorAMultiplier;
    void* noteCutInfo;
    void* saberAfterCutSwingRatingCounter;
    
} FlyingScoreEffect;

void checkJudgements(FlyingScoreEffect* scorePointer, int score) {
    log("Checking judgements for score: %i", score);
    int l = 6; // Constant for now, should be the length of judgements
    judgement_t best = judgements[5];
    for (int i = 4; i >= 0; i--) {
        if (judgements[i].threshold > score) {
            break;
        }
        best = judgements[i];
    }
    log("Setting score effect's color to best color with threshold: %i for score: %i", best.threshold, score);
    scorePointer->color.r = best.r;
    scorePointer->color.g = best.g;
    scorePointer->color.b = best.b;
    scorePointer->color.a = best.a;
    log("Modified color!");
}

MAKE_HOOK(raw_score_without_multiplier, 0x48C248, void, void* noteCutInfo, void* saberAfterCutSwingRatingCounter, int* beforeCutRawScore, int* afterCutRawScore, int* cutDistanceRawScore) {
    log("Called RawScoreWithoutMultiplier Hook!");
    raw_score_without_multiplier(noteCutInfo, saberAfterCutSwingRatingCounter, beforeCutRawScore, afterCutRawScore, cutDistanceRawScore);
}

MAKE_HOOK(init_and_present, 0x132307C, void, FlyingScoreEffect* self, void* noteCut, int multiplier, float duration, Vector3 targetPos, Color color, void* saberAfterCutSwingRatingCounter) {
    // Placeholder, for now.
    log("Called InitAndPresent Hook!");
    log("Attempting to call standard InitAndPresent...");
    init_and_present(self, noteCut, multiplier, duration, targetPos, color, saberAfterCutSwingRatingCounter);
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    raw_score_without_multiplier(noteCut, saberAfterCutSwingRatingCounter, &beforeCut, &afterCut, &cutDistance);
    int score = beforeCut + afterCut;
    log("RawScore: %i", score);
    log("Checking judgements...");
    checkJudgements(self, score);
    log("Completed InitAndPresent!");
}

MAKE_HOOK(HandleSaberAfterCutSwingRatingCounterDidChangeEvent, 0x13233DC, void, FlyingScoreEffect* self, void* saberAfterCutSwingRatingCounter, float rating) {
    log("Called HandleSaberAfterCutSwingRatingCounterDidChangeEvent Hook!");
    log("Attempting to call standard HandleSaberAfterCutSwingRatingCounterDidChangeEvent...");
    HandleSaberAfterCutSwingRatingCounterDidChangeEvent(self, saberAfterCutSwingRatingCounter, rating);
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    raw_score_without_multiplier(self->noteCutInfo, self->saberAfterCutSwingRatingCounter, &beforeCut, &afterCut, &cutDistance);
    int score = beforeCut + afterCut;
    log("RawScore: %i", score);
    log("Checking judgements...");
    checkJudgements(self, score);
    log("Completed HandleSaberAfterCutSwingRatingCounterDidChangeEvent!");
}

__attribute__((constructor)) void lib_main()
{
    log("Inserting HitScoreVisualizer...");
    INSTALL_HOOK(init_and_present);
    log("Installed InitAndPresent Hook!");
    INSTALL_HOOK(raw_score_without_multiplier);
    log("Installed RawScoreWithoutMultiplier Hook!");
    INSTALL_HOOK(HandleSaberAfterCutSwingRatingCounterDidChangeEvent);
    log("Installed HandleSaberAfterCutSwingRatingCounterDidChangeEvent Hook!");
    // Attempt to add and create judgements
    log("Attempting to create empty judgements array...");
    // judgements = malloc(sizeof(node_t));
    // Creating Fantastic judgement
    judgement_t fantastic = {115, 1.0f, 1.0f, 1.0f, 1.0f, "Fantastic\n"};
    judgements[0] = fantastic;
    // Creating Excellent judgement
    judgement_t excellent = {101, 0.0f, 1.0f, 0.0f, 1.0f, "<size=80%>Excellent</size>\n"};
    judgements[1] = excellent;
    // Creating Great judgement
    judgement_t great = {90, 1.0f, 0.980392158f, 0.0f, 1.0f, "<size=80%>Great</size>\n"};
    judgements[2] = great;
    // Creating Good judgement
    judgement_t good = {80, 1.0f, 0.6f, 0.0f, 1.0f, "<size=80%>Good</size>\n"};
    judgements[3] = good;
    // Creating Decent judgement
    judgement_t decent = {60, 1.0f, 0.0f, 0.0f, 1.0f, "<size=80%>Decent</size>\n"};
    judgements[4] = decent;
    // Creating Way Off judgement
    judgement_t way_off = {0, 0.5f, 0.0f, 0.0f, 1.0f, "<size=80%>Way Off</size>\n"};
    judgements[5] = way_off;
    log("Created default judgements!");

    // log("Attempting to load judgements from config!");
    // FILE* config = fopen("/sdcard/Android/data/com.beatgames.beatsaber/files/mods/hitscorevisualizer.cfg", "r");

    // log("Attempting to count number of lines in config!");
    // int count = 0; // Count of lines, count of judgements.
    // char c;

    // for (c = getc(config); c != EOF; c = getc(config)) 
    //     if (c == '\n') // Increment count if this character is newline 
    //         count = count + 1;

    // log("Found %i lines in config!", count);

    // for (int i = 0; i < count; i++) {
    //     log("Attempting to load judgement: %i", i);
    //     // Possible memory leakage?
    //     float* r = malloc(sizeof(float));
    //     float* g = malloc(sizeof(float));
    //     float* b = malloc(sizeof(float));
    //     float* a = malloc(sizeof(float));
    //     int* thresh = malloc(sizeof(int));
    //     char* text;
    //     // Possible memory leakage?
    //     judgement* judge = malloc(sizeof(judgement));
    //     log("Allocated memory for judgement");
    //     fscanf(config, "%f %f %f %f %i %s", r, g, b, a, thresh, text);
    //     log("Read judgement from file");
    //     judge->threshold = *thresh;
    //     judge->r = *r;
    //     judge->g = *g;
    //     judge->b = *b;
    //     judge->a = *a;
    //     judge->text = text;
    //     log("Populated fields of judgement!");
    //     add(judgements, judge);
    //     log("Added judge to judgements!");
    // }
    // log("Completed reading config!");
    // fclose(config);
}