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
#ifndef JSMN_INCLUDED
#include "../beatsaber-hook/jsmn/jsmn.h"
#endif

#undef log
#define log(...) __android_log_print(ANDROID_LOG_INFO, "QuestHook", "[HitScoreVisualizer v1.4.8.1] " __VA_ARGS__)

#define MAX_JSON_TOKENS 512
#define CONFIG_FILE "/sdcard/Android/data/com.beatgames.beatsaber/files/mods/HitScoreVisualizerConfig.json"

// TMP_Text.set_richText: 0x512540
#define TMP_Text_set_richText_offset 0x512540
// TMP_Text.set_enableWordWrapping: 0x51205C
#define TMP_Text_set_enableWordWrapping_offset 0x51205C
// TMP_Text.set_overflowMode: 0x512128
#define TMP_Text_set_oferflowMode_offset 0x512128
// TMP_Text.get_text: 0x510D88
#define TMP_Text_get_text_offset 0x510D88
// TMP_Text.set_text: 0x510D90
#define TMP_Text_set_text_offset 0x510D90
// ScoreController.RawScoreWithoutMultiplier: 0x48C248
#define RawScoreWithoutMulitplier_offset 0x48C248
// HandleSaberAfterCutSwingRatingCounterDidChangeEvent: 0x13233DC
#define HandleSaberAfterCutSwingRatingCounterDidChangeEvent_offset 0x13233DC

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

typedef struct judgement {
    int threshold;
    float r;
    float g;
    float b;
    float a;
    char* text;
    char fade;
} judgement_t;

typedef struct judgement_segment {
    int threshold;
    char* text;
} judgement_segment_t;

typedef enum DisplayMode {
    DISPLAY_MODE_FORMAT = 0,
    DISPLAY_MODE_NUMERIC = 1,
    DISPLAY_MODE_TEXTONLY = 2,
    DISPLAY_MODE_SCOREONTOP = 3,
    DISPLAY_MODE_TEXTONTOP = 4
} DisplayMode_t;

judgement_t* judgements;
int judgements_count = 0;
judgement_segment_t* beforeCutAngleJudgements;
int beforeCut_count = 0;
judgement_segment_t* accuracyJudgements;
int accuracy_count = 0;
judgement_segment_t* afterCutAngleJudgements;
int afterCut_count = 0;

DisplayMode_t display_mode;

void createdefaultjson(const char* filename) {
    const char* js = "\n{\n"
    "\t\"majorVersion\": 2,\n"
    "\t\"minorVersion\": 2,\n"
    "\t\"displayMode\": \"textOnTop\",\n"
    "\t\"judgements\":[\n"
    "\t{\n"
    "\t\t\"threshold\": 115,\n"
    "\t\t\"text\": \"%BFantastic%A%n%s\",\n"
    "\t\t\"color\": [\n"
    "\t\t\t1.0,\n"
    "\t\t\t1.0,\n"
    "\t\t\t1.0,\n"
    "\t\t\t1.0\n"
    "\t\t]\n"
    "\t},\n"
    "\t{\n"
    "\t\t\"threshold\": 101,\n"
    "\t\t\"text\": \"<size=80%>%BExcellent%A</size>%n%s\",\n"
    "\t\t\"color\": [\n"
    "\t\t\t0.0,\n"
    "\t\t\t1.0,\n"
    "\t\t\t0.0,\n"
    "\t\t\t1.0\n"
    "\t\t]\n"
    "\t},\n"
    "\t{\n"
    "\t\t\"threshold\": 90,\n"
    "\t\t\"text\": \"<size=80%>%BGreat%A</size>%n%s\",\n"
    "\t\t\"color\": [\n"
    "\t\t\t1.0,\n"
    "\t\t\t0.980392158,\n"
    "\t\t\t0.0,\n"
    "\t\t\t1.0\n"
    "\t\t]\n"
    "\t},\n"
    "\t{\n"
    "\t\t\"threshold\": 80,\n"
    "\t\t\"text\": \"<size=80%>%BGood%A</size>%n%s\",\n"
    "\t\t\"color\": [\n"
    "\t\t\t1.0,\n"
    "\t\t\t0.6,\n"
    "\t\t\t0.0,\n"
    "\t\t\t1.0\n"
    "\t\t],\n"
    "\t\t\"fade\": true\n"
    "\t},\n"
    "\t{\n"
    "\t\t\"threshold\": 60,\n"
    "\t\t\"text\": \"<size=80%>%BDecent%A</size>%n%s\",\n"
    "\t\t\"color\": [\n"
    "\t\t\t1.0,\n"
    "\t\t\t0.0,\n"
    "\t\t\t0.0,\n"
    "\t\t\t1.0\n"
    "\t\t],\n"
    "\t\t\"fade\": true\n"
    "\t},\n"
    "\t{\n"
    "\t\t\"text\": \"<size=80%>%BWay Off%A</size>%n%s\",\n"
    "\t\t\"color\": [\n"
    "\t\t\t0.5,\n"
    "\t\t\t0.0,\n"
    "\t\t\t0.0,\n"
    "\t\t\t1.0\n"
    "\t\t],\n"
    "\t\t\"fade\": true\n"
    "\t}\n"
    "\t],\n"
    "\t\"beforeCutAngleJudgments\": [\n"
    "\t{\n"
    "\t\t\"threshold\": 70,\n"
    "\t\t\"text\": \"+\"\n"
    "\t},\n"
    "\t{\n"
    "\t\t\"text\": \" \"\n"
    "\t}\n"
    "\t],\n"
    "\t\"accuracyJudgments\": [\n"
    "\t{\n"
    "\t\t\"threshold\": 15,\n"
    "\t\t\"text\": \"+\"\n"
    "\t},\n"
    "\t{\n"
    "\t\t\"text\": \" \"\n"
    "\t}\n"
    "\t],\n"
    "\t\"afterCutAngleJudgments\": [\n"
    "\t{\n"
    "\t\t\"threshold\": 30,\n"
    "\t\t\"text\": \"+\"\n"
    "\t},\n"
    "\t{\n"
    "\t\t\"text\": \" \"\n"
    "\t}\n"
    "\t]\n"
    "}";
    int r = writefile(filename, js);
    if (r == 0) {
        log("CREATED DEFAULT JSON FILE AT PATH: %s", filename);
    }
    else if (r == WRITE_ERROR_COULD_NOT_MAKE_FILE) {
        log("COULD NOT MAKE DEFAULT JSON FILE AT PATH: %s", filename);
    }
}

void createdefault() {
    judgements_count = 6;
    judgements = malloc(judgements_count * sizeof(judgement_t));
    // Creating Fantastic judgement
    judgement_t fantastic = {115, 1.0f, 1.0f, 1.0f, 1.0f, "Moon Struck!", '\0'};
    judgements[0] = fantastic;
    // Creating Excellent judgement
    judgement_t excellent = {101, 0.0f, 1.0f, 0.0f, 1.0f, "<size=80%>Sugar Crush!</size>", '\1'};
    judgements[1] = excellent;
    // Creating Great judgement
    judgement_t great = {90, 1.0f, 0.980392158f, 0.0f, 1.0f, "<size=80%>Divine</size>", '\1'};
    judgements[2] = great;
    // Creating Good judgement
    judgement_t good = {80, 1.0f, 0.6f, 0.0f, 1.0f, "<size=80%>Delicious</size>", '\1'};
    judgements[3] = good;
    // Creating Decent judgement
    judgement_t decent = {60, 1.0f, 0.0f, 0.0f, 1.0f, "<size=80%>Tasty</size>", '\1'};
    judgements[4] = decent;
    // Creating Way Off judgement
    judgement_t way_off = {0, 0.5f, 0.0f, 0.0f, 1.0f, "<size=80%>Sweet</size>", '\1'};
    judgements[5] = way_off;
    // Set displaymode
    display_mode = DISPLAY_MODE_TEXTONTOP;
    // Set BeforeCutSegments
    beforeCut_count = 2;
    beforeCutAngleJudgements = malloc(beforeCut_count * sizeof(judgement_segment_t));
    beforeCutAngleJudgements[0] = (judgement_segment_t) {70, "+"};
    beforeCutAngleJudgements[1] = (judgement_segment_t) {0, " "};
    // Set AccuracySegments
    accuracy_count = 2;
    accuracyJudgements = malloc(accuracy_count * sizeof(judgement_segment_t));
    accuracyJudgements[0] = (judgement_segment_t) {15, "+"};
    accuracyJudgements[1] = (judgement_segment_t) {0, " "};
    // Set AfterCut
    afterCut_count = 2;
    afterCutAngleJudgements = malloc(afterCut_count * sizeof(judgement_segment_t));
    afterCutAngleJudgements[0] = (judgement_segment_t) {30, "+"};
    afterCutAngleJudgements[1] = (judgement_segment_t) {0, " "};

    log("Created default judgements!");
}

void createjudgementsegments(const char* js, jsmntok_t* tokens, judgement_segment_t* segments, int current, int count) {
    int offset = 2;
    for (int j = 0; j < count; j++) {
        // For each segment
        jsmntok_t obj = tokens[current + j + offset];
        segments[j].threshold = 0;
        // LENGTH OF A SEGMENT STRUCT (ALL KEYS AND VALUES)
        int len = 4;
        for (int q = 0; q < len; q++) {
            // For each key, value in the segment
            char* buffer = bufferfromtoken(js, tokens[current + j + offset + q]);
            if (strcmp(buffer, "text") == 0) {
                segments[j].text = bufferfromtoken(js, tokens[current + j + offset + q + 1]);
                q += 1;
                continue;
            }
            else if (strcmp(buffer, "threshold") == 0) {
                // convert value buffer string to integer
                segments[j].threshold = intfromjson(js, tokens[current + j + offset + q + 1]);
                q += 1;
                continue;
            }
        }
        offset += len;
    }
}

void createjudgements(const char* js, jsmntok_t* tokens, judgement_t* judgements, int current) {
    int offset = 2;
    for (int j = 0; j < judgements_count; j++) {
        // For each judgement
        jsmntok_t judgementObj = tokens[current + j + offset];
        judgements[j].threshold = 0;
        printf("TRYING TOKEN: %i\n", current + j + offset);
        // LENGTH OF A JUDGEMENT STRUCT (ALL KEYS AND VALUES)
        int len = 10;
        if (judgementObj.size == 4) {
            len = 12;
        } else if (judgementObj.size == 3) {
            len = 10;
        } else {
            printf("LENGTH != 3 or 4 for token at: %i", current + j + offset);
            len = -1;
        }
        for (int q = 0; q < len; q++) {
            // For each item in the judgement object
            char* buffer = bufferfromtoken(js, tokens[current + j + offset + q]);
            if (strcmp(buffer, "text") == 0) {
                judgements[j].text = bufferfromtoken(js, tokens[current + j + offset + q + 1]);
                q += 1;
                continue;
            }
            if (strcmp(buffer, "threshold") == 0) {
                // convert value buffer string to integer
                judgements[j].threshold = intfromjson(js, tokens[current + j + offset + q + 1]);
                q += 1;
                continue;
            }
            if (strcmp(buffer, "color") == 0) {
                // convert value buffer strings to many floats
                judgements[j].r = doublefromjson(js, tokens[current + j + offset + q + 2]);
                judgements[j].g = doublefromjson(js, tokens[current + j + offset + q + 3]);
                judgements[j].b = doublefromjson(js, tokens[current + j + offset + q + 4]);
                judgements[j].a = doublefromjson(js, tokens[current + j + offset + q + 5]);
                q += 5;
                continue;
            }
            if (strcmp(buffer, "fade") == 0) {
                judgements[j].fade = boolfromjson(js, tokens[current + j + offset + q + 1]);
                q += 1;
                continue;
            }
        }
        offset += len;
    }
}

typedef enum judgementerr {
    JUDGEMENT_JSON_ERROR = -10,
    JUDGEMENT_VERSION_ERROR = -2,
    JUDGEMENT_MAJOR_VERSION_ERROR = -3,
    JUDGEMENT_MINOR_VERSION_ERROR = -4
} judgementerr_t;

int loadjudgements(const char* js) {
    jsmntok_t* tokens = malloc(MAX_JSON_TOKENS * sizeof(jsmntok_t));

    int count = parsejson(js, &tokens, MAX_JSON_TOKENS);
    if (count == JSMN_ERROR_INVAL) {
        createdefault();
        return JUDGEMENT_JSON_ERROR;
    }

    char version_match = '\0';
    
    for (int i = 0; i < count; i++) {
        // For each token
        // Create substring
        char* buffer = bufferfromtoken(js, tokens[i]);
        if (tokens[i].size > 0) {
            if (strcmp(buffer, "majorVersion") == 0) {
                // MajorVersion Key
                char* value = bufferfromtoken(js, tokens[i + 1]);
                if (strcmp(value, "2") < 0) {
                    // Invalid version, version is not 2.x, instead it is <2.x
                    // Return default.
                    createdefault();
                    return JUDGEMENT_MAJOR_VERSION_ERROR;
                }
                version_match = '\1';
                i++;
                continue;
            }
            else if (strcmp(buffer, "minorVersion") == 0) {
                // MinorVersion Key
                char* value = bufferfromtoken(js, tokens[i + 1]);
                if (strcmp(value, "2") < 0 || version_match != '\1') {
                    // Invalid version, version is not 2.2.x, instead it is <2.2.x
                    // Return default.
                    createdefault();
                    return JUDGEMENT_MINOR_VERSION_ERROR;
                }
                version_match = '\1';
                i++;
                continue;
            }
            else if (strcmp(buffer, "displayMode") == 0) {
                // DisplayMode
                char* temp = bufferfromtoken(js, tokens[i + 1]);
                if (strcmp(temp, "format") == 0) {
                    display_mode = DISPLAY_MODE_FORMAT;
                } else if (strcmp(temp, "numeric") == 0) {
                    display_mode = DISPLAY_MODE_NUMERIC;
                } else if (strcmp(temp, "textOnly") == 0) {
                    display_mode = DISPLAY_MODE_TEXTONLY;
                } else if (strcmp(temp, "scoreOnTop") == 0) {
                    display_mode = DISPLAY_MODE_SCOREONTOP;
                } else {
                    display_mode = DISPLAY_MODE_TEXTONTOP;
                }
                i++;
                continue;
            }
            else if (strcmp(buffer, "judgements") == 0) {
                if (version_match == '\0') {
                    // Version doesn't match. Return default.
                    createdefault();
                    return JUDGEMENT_VERSION_ERROR;
                }
                judgements_count = tokens[i + 1].size;
                judgements = malloc(judgements_count * sizeof(judgement_t));
                createjudgements(js, tokens, judgements, i);
            }
            else if (strcmp(buffer, "beforeCutAngleJudgments") == 0) {
                if (version_match == '\0') {
                    // Version doesn't match. Return default.
                    createdefault();
                    return JUDGEMENT_VERSION_ERROR;
                }
                beforeCut_count = tokens[i + 1].size;
                beforeCutAngleJudgements = malloc(beforeCut_count * sizeof(judgement_segment_t));
                createjudgementsegments(js, tokens, beforeCutAngleJudgements, i, beforeCut_count);
            }
            else if (strcmp(buffer, "accuracyJudgments") == 0) {
                if (version_match == '\0') {
                    // Version doesn't match. Return default.
                    createdefault();
                    return JUDGEMENT_VERSION_ERROR;
                }
                accuracy_count = tokens[i + 1].size;
                accuracyJudgements = malloc(accuracy_count * sizeof(judgement_segment_t));
                createjudgementsegments(js, tokens, accuracyJudgements, i, accuracy_count);
            }
            else if (strcmp(buffer, "afterCutAngleJudgments") == 0) {
                if (version_match == '\0') {
                    // Version doesn't match. Return default.
                    createdefault();
                    return JUDGEMENT_VERSION_ERROR;
                }
                afterCut_count = tokens[i + 1].size;
                afterCutAngleJudgements = malloc(afterCut_count * sizeof(judgement_segment_t));
                createjudgementsegments(js, tokens, afterCutAngleJudgements, i, afterCut_count);
            }
            // This is a key
        }
    }
    if (judgements && beforeCutAngleJudgements && accuracyJudgements && afterCutAngleJudgements) {
        return 0;
    }
    createdefault();
    return JUDGEMENT_JSON_ERROR;
}
int loadjudgementsfile(const char* filename) {
    const char* js = readfile(filename);
    if (js) {
        return loadjudgements(js);
    }
    return PARSE_ERROR_FILE_DOES_NOT_EXIST;
}

char* getBestSegment(judgement_segment_t* segments, int totalCount, int comparison) {
    judgement_segment_t best = segments[totalCount - 1];
    for (int i = totalCount - 2; i >= 0; i--) {
        if (segments[i].threshold > comparison) {
            break;
        }
        best = segments[i];
    }
    return best.text;
}

void checkJudgements(FlyingScoreEffect* scorePointer, int beforeCut, int afterCut, int cutDistance) {
    int score = beforeCut + afterCut;
    log("Checking judgements for score: %i", score);
    judgement_t best = judgements[judgements_count - 1];
    for (int i = judgements_count-2; i >= 0; i--) {
        if (judgements[i].threshold > score) {
            break;
        }
        best = judgements[i];
    }
    log("Setting score effect's color to best color with threshold: %i for score: %i", best.threshold, score);
    // TODO Add fading
    scorePointer->color.r = best.r;
    scorePointer->color.g = best.g;
    scorePointer->color.b = best.b;
    scorePointer->color.a = best.a;
    log("Modified color!");
    log("Setting rich text...");
    
    void (*set_richText)(void*, char) = (void*)getRealOffset(TMP_Text_set_richText_offset);
    set_richText(scorePointer->text, 0x1);
    log("Disabling word wrap...");
    
    void (*set_enableWordWrapping)(void*, char) = (void*)getRealOffset(TMP_Text_set_enableWordWrapping_offset);
    set_enableWordWrapping(scorePointer->text, 0x0);
    log("Setting overflow option...");
    
    void (*set_overflowMode)(void*, int) = (void*)getRealOffset(TMP_Text_set_oferflowMode_offset);
    set_overflowMode(scorePointer->text, 0x0);
    log("Attempting to get text...");
    
    cs_string* (*get_text)(void*) = (void*)getRealOffset(TMP_Text_get_text_offset);
    cs_string* old = get_text(scorePointer->text);

    log("Attempting to create judgement_cs string...");
    cs_string* newText = NULL;
    // System.String.Concat: 0x972F2C
    cs_string* (*concat)(cs_string*, cs_string*) = (void*)getRealOffset(CONCAT_STRING_OFFSET);
    // System.String.Replace: 0x97FF04
    cs_string* (*replace)(cs_string*, cs_string*, cs_string*) = (void*)getRealOffset(STRING_REPLACE_OFFSET);
    // Create default judgement_cs:
    cs_string* judgement_cs = createcsstr(best.text, strlen(best.text));
    switch (display_mode)
    {
    case DISPLAY_MODE_FORMAT:
        // THIS IS VERY INEFFICIENT AND SLOW BUT SHOULD WORK!
        log("Displaying formated text!");
        char buffer[4]; // Max length for score buffers is 3
        // %b
        sprintf(buffer, "%i", beforeCut);
        judgement_cs = replace(judgement_cs, createcsstr("%b", 2), createcsstr(buffer, strlen(buffer)));
        // %c
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%i", cutDistance);
        judgement_cs = replace(judgement_cs, createcsstr("%c", 2), createcsstr(buffer, strlen(buffer)));
        // %a
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%i", afterCut);
        judgement_cs = replace(judgement_cs, createcsstr("%a", 2), createcsstr(buffer, strlen(buffer)));
        // %B
        char* bestBeforeSeg = getBestSegment(beforeCutAngleJudgements, beforeCut_count, beforeCut);
        judgement_cs = replace(judgement_cs, createcsstr("%B", 2), createcsstr(bestBeforeSeg, strlen(bestBeforeSeg)));
        // %C
        char* bestCutAcc = getBestSegment(accuracyJudgements, accuracy_count, cutDistance);
        judgement_cs = replace(judgement_cs, createcsstr("%C", 2), createcsstr(bestCutAcc, strlen(bestCutAcc)));
        // %A
        char* bestAfterSeg = getBestSegment(afterCutAngleJudgements, afterCut_count, afterCut);
        judgement_cs = replace(judgement_cs, createcsstr("%A", 2), createcsstr(bestAfterSeg, strlen(bestAfterSeg)));
        // %s
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%i", score);
        judgement_cs = replace(judgement_cs, createcsstr("%s", 2), createcsstr(buffer, strlen(buffer)));
        // %p
        char percentBuff[7]; // 6 is upper bound for 100.00 percent
        sprintf(percentBuff, "%.2f", score / 115.0 * 100.0);
        judgement_cs = replace(judgement_cs, createcsstr("%p", 2), createcsstr(percentBuff, strlen(percentBuff)));
        // %%
        judgement_cs = replace(judgement_cs, createcsstr("%%", 2), createcsstr("%", 1));
        // %n
        judgement_cs = replace(judgement_cs, createcsstr("%n", 2), createcsstr("\n", 1));
        newText = judgement_cs;
        break;
    case DISPLAY_MODE_NUMERIC:
        // Numeric display ONLY
        log("Displaying numeric text ONLY!");
        newText = old;
        break;
    case DISPLAY_MODE_SCOREONTOP:
        // Score on top
        log("Displaying score on top!");
        // Add newline
        cs_string* temp = concat(old, createcsstr("\n", 1));
        log("Attempting to concat old text and judgement text...");
        newText = concat(temp, judgement_cs);
        break;
    case DISPLAY_MODE_TEXTONTOP:
    default:
        // Text on top
        log("Displaying judgement text on top!");
        // Add newline
        judgement_cs = concat(judgement_cs, createcsstr("\n", 1));
        log("Attempting to concat judgement text and old text...");
        newText = concat(judgement_cs, old);
        break;
    }
    

    log("Calling set_text...");
    
    void (*set_text)(void*, cs_string*) = (void*)getRealOffset(TMP_Text_set_text_offset);
    set_text(scorePointer->text, newText);

    log("Complete!");
}

MAKE_HOOK(raw_score_without_multiplier, RawScoreWithoutMulitplier_offset, void, void* noteCutInfo, void* saberAfterCutSwingRatingCounter, int* beforeCutRawScore, int* afterCutRawScore, int* cutDistanceRawScore) {
    log("Called RawScoreWithoutMultiplier Hook!");
    raw_score_without_multiplier(noteCutInfo, saberAfterCutSwingRatingCounter, beforeCutRawScore, afterCutRawScore, cutDistanceRawScore);
}

MAKE_HOOK(HandleSaberAfterCutSwingRatingCounterDidChangeEvent, HandleSaberAfterCutSwingRatingCounterDidChangeEvent_offset, void, FlyingScoreEffect* self, void* saberAfterCutSwingRatingCounter, float rating) {
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
    checkJudgements(self, beforeCut, afterCut, cutDistance);
    log("Completed HandleSaberAfterCutSwingRatingCounterDidChangeEvent!");
}

__attribute__((constructor)) void lib_main()
{
    log("Inserting HitScoreVisualizer...");
    // INSTALL_HOOK(init_and_present);
    // log("Installed InitAndPresent Hook!");
    INSTALL_HOOK(raw_score_without_multiplier);
    log("Installed RawScoreWithoutMultiplier Hook!");
    INSTALL_HOOK(HandleSaberAfterCutSwingRatingCounterDidChangeEvent);
    log("Installed HandleSaberAfterCutSwingRatingCounterDidChangeEvent Hook!");
    // Attempt to add and create judgements
    // Attempt to find judgements
    if (fileexists(CONFIG_FILE) == '\1') {
        int r = loadjudgementsfile(CONFIG_FILE);
        if (r == PARSE_ERROR_FILE_DOES_NOT_EXIST) {
            log("File at path: %s does not exist!", CONFIG_FILE);
            createdefaultjson(CONFIG_FILE);
        } else if (r == JUDGEMENT_JSON_ERROR) {
            log("Judgement JSON Error! Invalid JSON at path: %s", CONFIG_FILE);
        } else if (r == JUDGEMENT_VERSION_ERROR) {
            log("Judgement JSON Version mismatch! Expected version >=2.2.0! At path: %s", CONFIG_FILE);
        } else if (r == 0) {
            log("Loaded judgements sucessfully!");
        }
    } else {
        createdefaultjson(CONFIG_FILE);
        createdefault();
    }
}