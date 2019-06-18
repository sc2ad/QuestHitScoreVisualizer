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

typedef struct node
{
    judgement_t* value;
    struct node* next;
} node_t;

float temp_r = 1;
float temp_g = 0;
float temp_b = 0;
float temp_a = 1;
node_t* judgements = NULL;

judgement_t* get(node_t* head, int index) {
    node_t* current = head;
    int cI = 0;
    while (cI < index) {
        if (current == NULL) {
            return NULL;
        }
        current = current->next;
        cI++;
    }
    return current->value;
}

int size(node_t* head) {
    int length = 0;
    node_t* current = head;
    while (current != NULL) {
        current = current->next;
        length++;
    }
    return length;
}

void add(node_t* head, judgement_t* value) {
    if (head == NULL) {
        return;
    }
    node_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(node_t));
    current->next->value = value;
    current->next->next = NULL;
}

typedef struct __attribute__((__packed__)) {
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct __attribute__((__packed__)) {
    // First field begins at 0x58, could fill in useless
    // byte data here to just "take up space"
    char data[0x58];
    void* fadeAnimationCurve;
    void* maxCutDistanceScoreIndicator;
    void* text;
    Color* color;
    float colorAMultiplier;
    void* noteCutInfo;
    void* saberAfterCutSwingRatingCounter;
    
} FlyingScoreEffect;

void checkJudgements(FlyingScoreEffect* scorePointer, int score) {
    log("Checking judgements for score: %i", score);
    int l = size(judgements);
    log("Beginning for loop...");
    judgement_t* best = get(judgements, 0);
    for (int i = 1; i < l; i++) {
        if (get(judgements, i)->threshold > score) {
            break;
        }
        best = get(judgements, i);
        log("Setting new best judgement at index %i with text %s", i, best->text);
    }
    log("Setting score effect's color to best color with threshold: %i", best->threshold);
    scorePointer->color->r = best->r;
    scorePointer->color->g = best->g;
    scorePointer->color->b = best->b;
    scorePointer->color->a = best->a;
    log("Complete!");
}

MAKE_HOOK(raw_score_without_multiplier, 0x48C248, void, void* noteCutInfo, void* saberAfterCutSwingRatingCounter, int* beforeCutRawScore, int* afterCutRawScore, int* cutDistanceRawScore) {
    log("Called RawScoreWithoutMultiplier Hook!");
    raw_score_without_multiplier(noteCutInfo, saberAfterCutSwingRatingCounter, beforeCutRawScore, afterCutRawScore, cutDistanceRawScore);
}

MAKE_HOOK(init_and_present, 0x132307C, void, FlyingScoreEffect* self, void* noteCut, int multiplier, float duration, void* targetPos, Color* color, void* saberAfterCutSwingRatingCounter) {
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
    log("Inserted HitScoreVisualizer to only display color: %f, %f, %f", temp_r, temp_g, temp_b);
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
    judgements = malloc(sizeof(node_t));
    // Creating Fantastic judgement
    judgement_t* fantastic = malloc(sizeof(judgement_t));
    fantastic->r = 1.0f;
    fantastic->g = 1.0f;
    fantastic->b = 1.0f;
    fantastic->a = 1.0f;
    fantastic->text = "Fantastic\n";
    fantastic->threshold = 115;
    add(judgements, fantastic);
    // Creating Excellent judgement
    judgement_t* excellent = malloc(sizeof(judgement_t));
    excellent->r = 0.0f;
    excellent->g = 1.0f;
    excellent->b = 0.0f;
    excellent->a = 1.0f;
    excellent->text = "<size=80%>Excellent</size>\n";
    excellent->threshold = 101;
    add(judgements, excellent);
    // Creating Great judgement
    judgement_t* great = malloc(sizeof(judgement_t));
    great->r = 1.0f;
    great->g = 0.980392158f;
    great->b = 0.0f;
    great->a = 1.0f;
    great->text = "<size=80%>Great</size>\n";
    great->threshold = 90;
    add(judgements, great);
    // Creating Good judgement
    judgement_t* good = malloc(sizeof(judgement_t));
    good->r = 1.0f;
    good->g = 0.6f;
    good->b = 0.0f;
    good->a = 1.0f;
    good->text = "<size=80%>Good</size>\n";
    good->threshold = 80;
    add(judgements, good);
    // Creating Decent judgement
    judgement_t* decent = malloc(sizeof(judgement_t));
    decent->r = 1.0f;
    decent->g = 0.0f;
    decent->b = 0.0f;
    decent->a = 1.0f;
    decent->text = "<size=80%>Decent</size>\n";
    decent->threshold = 60;
    add(judgements, decent);
    // Creating Way Off judgement
    judgement_t* way_off = malloc(sizeof(judgement_t));
    way_off->r = 0.5f;
    way_off->g = 0.0f;
    way_off->b = 0.0f;
    way_off->a = 1.0f;
    way_off->text = "<size=80%>Way Off</size>\n";
    way_off->threshold = 0;
    add(judgements, way_off);

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