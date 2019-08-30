#ifndef HITSCOREVISUALIZER_H
#define HITSCOREVISUALIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <vector>
#include <unordered_map>

#include "../beatsaber-hook/shared/utils/rapidjson-utils.h"
#include "../beatsaber-hook/shared/utils/utils.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_Object.h"

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

struct Config {
    int majorVersion;
    int minorVersion;
    int patchVersion;
    DisplayMode displayMode;
    std::vector<judgement> judgements;
    std::vector<judgement_segment> beforeCutAngleJudgements;
    std::vector<judgement_segment> accuracyJudgements;
    std::vector<judgement_segment> afterCutAngleJudgements;
} Config;

typedef struct FlyingObjectEffect : UnityEngine_Object::Class {
    // Fields
	void* _moveAnimationCurve; // 0xC
	float _shakeFrequency; // 0x10
	float _shakeStrength; // 0x14
	void* _shakeStrengthAnimationCurve; // 0x18
	void* didFinishEvent; // 0x1C
	bool _initialized; // 0x20
	Quaternion _rotation; // 0x24
	float _elapsedTime; // 0x34
	Vector3 _startPos; // 0x38
	Vector3 _targetPos; // 0x44
	float _duration; // 0x50
	uint32_t _shake; // 0x54
} FlyingObjectEffect;

typedef struct FlyingScoreEffect : FlyingObjectEffect {
    void* fadeAnimationCurve; // 0x58
    void* maxCutDistanceScoreIndicator; // 0x5C
    void* text; // TextMeshPro (base class: TMP_Text) // 0x60
    Color color; // 0x64
    float colorAMultiplier; // 0x74
    void* noteCutInfo; // 0x78
    void* saberAfterCutSwingRatingCounter; // 0x7C
    
} FlyingScoreEffect;

#endif /* HITSCOREVISUALIZER_H */