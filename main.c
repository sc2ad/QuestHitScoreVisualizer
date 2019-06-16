#include <android/log.h>
#include <stdlib.h>
#include <time.h>
#include <stdalign.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "beatsaber-hook/shared/inline-hook/inlineHook.h"
#include "beatsaber-hook/shared/utils/utils.h"

typedef struct __attribute__((__packed__)) {
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct __attribute__((__packed__)) {
    void* fadeAnimationCurve;
    void* maxCutDistanceScoreIndicator;
    void* text;
    Color* color;
    float colorAMultiplier;
    void* noteCutInfo;
    void* saberAfterCutSwingRatingCounter;
    
} FlyingScoreEffect;

float temp_r = 1.0f;
float temp_g = 0f;
float temp_b = 0f;
float temp_a = 1f;

MAKE_HOOK_NAT(init_and_present, 0x132307C, void, struct* noteCut, int multiplier, float duration, struct* targetPos, struct Color* color, struct* saberAfterCutSwingRatingCounter) {
    // Placeholder, for now.
}

MAKE_HOOK_NAT(manual_update, 0x1323314, void, FlyingScoreEffect* self, float t) {
    // Lets just test to make sure this one works without running the actual ones that would change color based on hit score
    log("Attempting to create new pointer to color with self pointer: %i", self);
    self->color = malloc(sizeof(Color));
    log("Completed malloc for Color struct!");
    log("Attemping to set color to: %f, %f, %f", temp_r, temp_g, temp_b);
    self->color->r = temp_r;
    self->color->g = temp_g;
    self->color->b = temp_b;
    self->color->a = temp_a;
    log("Set color to: %f, %f, %f", temp_r, temp_g, temp_b);
    manual_update(self, t);
}

__attribute__((constructor)) void lib_main()
{
    log("Inserted HitScoreVisualizer to only display color: %f, %f, %f", temp_r, temp_g, temp_b);
    INSTALL_HOOK_NAT(manual_update);
    log("Installed hook!");
}