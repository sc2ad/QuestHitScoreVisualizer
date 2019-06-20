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
    log("Beginning for loop...");
    judgement_t best = judgements[0];
    for (int i = 1; i < l; i++) {
        if (judgements[i].threshold <= score) {
            break;
        }
        best = judgements[i];
        log("Setting new best judgement at index %i with text %s", i, best.text);
    }
    log("Setting score effect's color to best color with threshold: %i", best.threshold);
    scorePointer->color.r = best.r;
    scorePointer->color.g = best.g;
    scorePointer->color.b = best.b;
    scorePointer->color.a = best.a;
    log("Complete!");
}

MAKE_HOOK(raw_score_without_multiplier, 0x48C248, void, void* noteCutInfo, void* saberAfterCutSwingRatingCounter, int* beforeCutRawScore, int* afterCutRawScore, int* cutDistanceRawScore) {
    log("Called RawScoreWithoutMultiplier Hook!");
    raw_score_without_multiplier(noteCutInfo, saberAfterCutSwingRatingCounter, beforeCutRawScore, afterCutRawScore, cutDistanceRawScore);
}

// RELEVANT GHIDRA DUMP OF INIT AND PRESENT

// FULL PARAMETERS: (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            //    undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            //    undefined4 param_9,undefined4 param_10,undefined4 param_11,int param_12)

// COMPARED TO IL2CPP DUMPER: (this, NoteCutInfo noteCutInfo, int multiplier, float duration, Vector3 targetPos, 
            //    Color color, SaberAfterCutSwingRatingCounter saberAfterCutSwingRatingCounter)

//   *(undefined4 *)(param_1 + 100) = param_8; <-- I don't know what this is
// SO... color starts at 0x64, but the first param is at 0x68... Not sure why
// THEN, there are more params (each is only 4 bytes, it seems that they are the r,g,b values of the color?)
// THE weird thing is that it then ends at 0x74, which is significantly different than 0x78 (next field)
// AND why are the parameters even fed in directly like this?
//   *(undefined4 *)(param_1 + 0x68) = param_9;
//   *(undefined4 *)(param_1 + 0x6c) = param_10;
//   *(undefined4 *)(param_1 + 0x70) = param_11;
//   *(undefined4 *)(param_1 + 0x78) = param_2; //_noteCutInfo
//   *(int *)(param_1 + 0x7c) = param_12; //_saberAfterCutSwingRatingCounter
//   FUN_00493dc0(param_12,uVar1,0);
//   ScoreController.RawScoreWithoutMultiplier(param_2,param_12,&local_2c,&local_30,&local_34,0);
//   iVar2 = *(int *)(param_1 + 0x60); //_text
//   local_28 = local_30 + local_2c;
//   uVar1 = FUN_01395cc0(&local_28,0); //this.GetScoreText(score)
//   FUN_00520d90(iVar2,uVar1,0);
//   FUN_00bf01d8(*(int *)(param_1 + 0x5c),(uint)(local_34 == 0xf),0); //_maxCutDistanceScoreIndicator
//   uVar1 = 0x3e99999a;
//   if (0x67 < local_30 + local_2c) {
//     uVar1 = 0x3f800000;
//   }
//   *(undefined4 *)(param_1 + 0x74) = uVar1; //_colorAMultiplier
//   FUN_01332bf0(param_1,param_4,param_5,param_6,param_7,0); //base.InitAndPresent(duration, vector3, false)
//   return;

MAKE_HOOK(init_and_present, 0x132307C, void, FlyingScoreEffect* self, void* noteCut, int multiplier, float duration, Vector3 targetPos, Color color, void* saberAfterCutSwingRatingCounter) {
    // Placeholder, for now.
    log("Called InitAndPresent Hook!");
    log("Attempting to call standard InitAndPresent...");
    init_and_present(self, noteCut, multiplier, duration, targetPos, color, saberAfterCutSwingRatingCounter);
    log("Creating score ints!");
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    log("Attempting to call RawScoreWithoutMultiplier hook...");
    raw_score_without_multiplier(noteCut, saberAfterCutSwingRatingCounter, &beforeCut, &afterCut, &cutDistance);
    log("Completed!");
    int score = afterCut + cutDistance;
    log("RawScore: %i", score);
    log("Checking judgements...");
    checkJudgements(self, score);
}

MAKE_HOOK(HandleSaberAfterCutSwingRatingCounterDidChangeEvent, 0x13233DC, void, FlyingScoreEffect* self, void* saberAfterCutSwingRatingCounter, float rating) {
    log("Called HandleSaberAfterCutSwingRatingCounterDidChangeEvent Hook!");
    log("Attempting to call standard HandleSaberAfterCutSwingRatingCounterDidChangeEvent...");
    HandleSaberAfterCutSwingRatingCounterDidChangeEvent(self, saberAfterCutSwingRatingCounter, rating);
    log("Creating score ints!");
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    log("Attempting to call RawScoreWithoutMultiplier hook...");
    raw_score_without_multiplier(self->noteCutInfo, self->saberAfterCutSwingRatingCounter, &beforeCut, &afterCut, &cutDistance);
    log("Completed!");
    int score = afterCut + cutDistance;
    log("RawScore: %i", score);
    log("Checking judgements...");
    checkJudgements(self, score);
}

MAKE_HOOK(manual_update, 0x1323314, void, FlyingScoreEffect* self, float t) {
    // log("Attemping to set color to: %f, %f, %f, %f", temp_r, temp_g, temp_b, temp_a);
    // self->color->r = temp_r;
    // self->color->g = temp_g;
    // self->color->b = temp_b;
    // self->color->a = temp_a;
    // log("Set color to: %f, %f, %f, %f", temp_r, temp_g, temp_b, temp_a);
    log("Calling ManualUpdate!");
    manual_update(self, t);
}

__attribute__((constructor)) void lib_main()
{
    log("Inserting HitScoreVisualizer...");
    INSTALL_HOOK(manual_update);
    log("Installed ManualUpdate Hook!");
    INSTALL_HOOK(init_and_present);
    log("Installed InitAndPresent Hook!");
    INSTALL_HOOK(raw_score_without_multiplier);
    log("Installed RawScoreWithoutMultiplier Hook!");
    INSTALL_HOOK(HandleSaberAfterCutSwingRatingCounterDidChangeEvent);
    log("Installed HandleSaberAfterCutSwingRatingCounterDidChangeEvent Hook!");
    // Attempt to add and create judgements
    log("Attempting to create empty judgements linked list...");
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