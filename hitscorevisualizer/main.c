#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <wchar.h>
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

typedef struct {
    // First field begins at 0x58, could fill in useless
    // byte data here to just "take up space"
    char data[0x58];
    void* fadeAnimationCurve;
    void* maxCutDistanceScoreIndicator;
    void* text; // TextMeshPro (base class: TMP_Text)
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
    log("Setting rich text...");
    // TMP_Text.set_richText: 0x512540
    void (*set_richText)(void*, char) = (void*)getRealOffset(0x512540);
    set_richText(scorePointer->text, 0x1);
    log("Disabling word wrap...");
    // TMP_Text.set_enableWordWrapping: 0x51205C
    void (*set_enableWordWrapping)(void*, char) = (void*)getRealOffset(0x51205C);
    set_enableWordWrapping(scorePointer->text, 0x0);
    log("Setting overflow option...");
    // TMP_Text.set_overflowMode: 0x512128
    void (*set_overflowMode)(void*, int) = (void*)getRealOffset(0x512128);
    set_overflowMode(scorePointer->text, 0x0);
    log("Attempting to get text...");
    // TMP_Text.get_text: 0x510D88
    cs_string* (*get_text)(void*) = (void*)getRealOffset(0x510D88);
    cs_string* old = get_text(scorePointer->text);
    log("Attempting to create new C# string...");
    cs_string* judgement_cs = malloc(sizeof(cs_string));
    log("Attempting to set new string to judgement text...");
    setcsstr(judgement_cs, best.text);
    log("Attempting to concat judgement text and old text...");
    // System.string.Concat: 0x972F2C
    cs_string* (*concat)(cs_string*, cs_string*) = (void*)getRealOffset(0x972F2C);
    cs_string* newText = concat(judgement_cs, old);
    log("Attempting to overwrite old text with newText...");
    setcswstr(old, newText->str);
    log("Freeing new text...");
    free(judgement_cs);
    // // FOR NOW, LET'S SEE IF WE CAN JUST COMPLETELY OVERWRITE THE TEXT TO SOMETHING DIFFERENT
    // log("Attempting to store old text...");
    // // THIS IS SUPER SCARY AND A COMPLETE HACK BUT IF IT WORKS, IT WORKS
    // int oLen = old->len;
    // log("Old length of string: %i", oLen);
    // unsigned short score1 = old->str[0];
    // unsigned short score2;
    // unsigned short score3;
    // log("Saved score: %i", score1);
    // if (oLen >= 2) {
    //     score2 = old->str[1];
    //     log("Saved score: %i", score2);
    // }
    // if (oLen >= 3) {
    //     score3 = old->str[2];
    //     log("Saved score: %i", score3);
    // }
    // // char* oldText;
    // // csstrtostr(old, oldText);
    
    // log("Attempting to set text to judgement...");
    // // strcat(oldText, best.text);
    // // setcsstr(old, oldText);
    // // setcsstr(old, best.text);

    // log("Attempting to get length of judgement str");
    // int strL = strlen(best.text);
    // log("String length: %i", strL);
    // log("PRE-OVERWRITE DUMP AT: %i", (int)old->str);
    // for (int i = 0; i < 50; i++) {
    //     log("Byte at %i is: %i", (int)old->str + i, *(char*)((int)old->str + i));
    // }
    // for (int i = 0; i < strL; i++) {
    //     old->str[i] = (unsigned short)best.text[i];
    //     old->len += 1;
    // }
    // log("Appending score text...");
    // old->str[old->len] = score1;
    // log("Appended: %i", old->str[old->len]);
    // old->len += 1;
    // if (oLen >= 2) {
    //     old->str[old->len] = score2;
    //     log("Appended: %i", old->str[old->len]);
    //     old->len += 1;
    // }
    // if (oLen >= 3) {
    //     old->str[old->len] = score3;
    //     log("Appended: %i", old->str[old->len]);
    //     old->len += 1;
    // }
    // log("New length: %i", old->len);
    // log("POST-OVERWRITE DUMP AT: %i", (int)old->str);
    // for (int i = 0; i < 50; i++) {
    //     log("Byte at %i is: %i", (int)old->str + i, *(char*)((int)old->str + i));
    // }

    // old->str[0] = (short)L'M';
    // old->str[1] = (short)L'Y';
    // old->str[2] = (short)L' ';
    // old->str[3] = (short)L'C';
    // old->str[4] = (short)L'U';
    // old->str[5] = (short)L'S';
    // old->str[6] = (short)L'T';
    // old->str[7] = (short)L'O';
    // old->str[8] = (short)L'M';

    log("Complete!");
}

MAKE_HOOK(raw_score_without_multiplier, 0x48C248, void, void* noteCutInfo, void* saberAfterCutSwingRatingCounter, int* beforeCutRawScore, int* afterCutRawScore, int* cutDistanceRawScore) {
    log("Called RawScoreWithoutMultiplier Hook!");
    raw_score_without_multiplier(noteCutInfo, saberAfterCutSwingRatingCounter, beforeCutRawScore, afterCutRawScore, cutDistanceRawScore);
}

MAKE_HOOK(init_and_present, 0x132307C, void, FlyingScoreEffect* self, void* noteCut, int multiplier, float duration, Vector3 targetPos, Color color, void* saberAfterCutSwingRatingCounter) {
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
}