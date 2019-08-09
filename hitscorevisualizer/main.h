#ifndef HITSCOREVISUALIZER_H
#define HITSCOREVISUALIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unordered_map>

#include "../beatsaber-hook/shared/utils/rapidjson-utils.h"

#ifndef __cplusplus
#define bool uint8_t
#endif /* __cplusplus */

typedef struct judgement {
    int threshold;
    float r;
    float g;
    float b;
    float a;
    const char* text;
    bool fade;
} judgement;

typedef struct judgement_segment {
    int threshold;
    const char* text;
} judgement_segment;

typedef enum DisplayMode {
    DISPLAY_MODE_FORMAT = 0,
    DISPLAY_MODE_NUMERIC = 1,
    DISPLAY_MODE_TEXTONLY = 2,
    DISPLAY_MODE_SCOREONTOP = 3,
    DISPLAY_MODE_TEXTONTOP = 4
} DisplayMode;

typedef struct Config {
    int majorVersion;
    int minorVersion;
    int patchVersion;
    DisplayMode displayMode;
    std::vector<judgement> judgements;
    std::vector<judgement_segment> beforeCutAngleJudgements;
    std::vector<judgement_segment> accuracyJudgements;
    std::vector<judgement_segment> afterCutAngleJudgements;
} Config;

#endif /* HITSCOREVISUALIZER_H */