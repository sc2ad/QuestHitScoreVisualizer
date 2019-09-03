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
	void* _moveAnimationCurve; // 0x18
	float _shakeFrequency; // 0x20
	float _shakeStrength; // 0x24
	void* _shakeStrengthAnimationCurve; // 0x28
	void* didFinishEvent; // 0x30
	uint32_t _initialized; // 0x38
	Quaternion _rotation; // 0x3C
	float _elapsedTime; // 0x4C
	Vector3 _startPos; // 0x50
	Vector3 _targetPos; // 0x5C
	float _duration; // 0x68
	uint32_t _shake; // 0x6C
} FlyingObjectEffect;

typedef struct FlyingScoreEffect : FlyingObjectEffect {
    void* _fadeAnimationCurve; // 0x70
	void* _maxCutDistanceScoreIndicator; // 0x78
	void* _text; // 0x80
	Color _color; // 0x88
	float _colorAMultiplier; // 0x98
	void* _noteCutInfo; // 0xA0
} FlyingScoreEffect;

#endif /* HITSCOREVISUALIZER_H */