#include "HSV.hpp"
#include "utils.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/utils.h"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

std::optional<Color> HSV::fadeBetween(judgment from, judgment to, int score, Color initialColor) {
    auto reverseLerp = RET_NULLOPT_UNLESS(il2cpp_utils::RunMethod<float>("UnityEngine", "Mathf", "InverseLerp", (float)from.threshold, (float)to.threshold, (float)score));
    auto fadeToColor = RET_NULLOPT_UNLESS(to.color);
    return RET_NULLOPT_UNLESS(il2cpp_utils::RunMethod<Color>("UnityEngine", "Color", "Lerp", initialColor, fadeToColor, reverseLerp));
}

bool HSV::addColor(Il2CppObject* flyingScoreEffect, int bestIndex, int score) {
    getLogger().debug("Adding color for bestIndex: %d, score: %d", bestIndex, score);
    std::optional<Color> color = config.judgments[bestIndex].color;
    if (config.judgments[bestIndex].fade.value_or(false) && bestIndex != 0 && color) {
        color = fadeBetween(config.judgments[bestIndex], config.judgments[bestIndex - 1], score, *color);
    }

    if (color) {
        RET_F_UNLESS(il2cpp_utils::SetFieldValue(flyingScoreEffect, "_color", *color));
    } else {
        // Use default color of white (instead of whatever the previous color was)
        RET_F_UNLESS(il2cpp_utils::SetFieldValue(flyingScoreEffect, "_color", (Color){1.0f, 1.0f, 1.0f, 1.0f}));
    }
    return true;
}

bool HSV::addText(Il2CppObject* flyingScoreEffect, judgment best, int beforeCut, int afterCut, int cutDistance) {
    if (!best.tokenizedText && !requires_text(config.displayMode)) {
        // Don't load any customized text if there is no need to
        // ex: imageOnly, no text provided
        return true;
    }
    Il2CppObject* text = RET_F_UNLESS(il2cpp_utils::GetFieldValue(flyingScoreEffect, "_text").value_or(nullptr));

    Il2CppString* judgment_cs = nullptr;
    if (config.displayMode == DISPLAY_MODE_FORMAT) {
        RET_F_UNLESS(best.tokenizedText);
        judgment_cs = parseFormattedText(best, beforeCut, afterCut, cutDistance);
    } else if (config.displayMode == DISPLAY_MODE_NUMERIC) {
        RET_F_UNLESS(best.tokenizedText);
        // Numeric display ONLY
        judgment_cs = RET_F_UNLESS(il2cpp_utils::GetPropertyValue<Il2CppString*>(text, "text"));
    } else if (config.displayMode == DISPLAY_MODE_SCOREONTOP) {
        RET_F_UNLESS(best.tokenizedText);
        // Score on top
        // Add newline
        judgment_cs = RET_F_UNLESS(il2cpp_utils::GetPropertyValue<Il2CppString*>(text, "text"));
        // Faster to convert the old text, use c++ strings, convert it back than it is to use C# string.Concat twice (with two created C# strings)
        judgment_cs = il2cpp_utils::createcsstr(to_utf8(csstrtostr(judgment_cs)) + "\n" + best.tokenizedText->Join());
    } else if (config.displayMode == DISPLAY_MODE_TEXTONLY) {
        // Will not display images, use formatted display
        RET_F_UNLESS(best.tokenizedText);
        judgment_cs = parseFormattedText(best, beforeCut, afterCut, cutDistance);
    } else if (config.displayMode == DISPLAY_MODE_TEXTONTOP) {
        RET_F_UNLESS(best.tokenizedText);
        // Text on top
        judgment_cs = RET_F_UNLESS(il2cpp_utils::GetPropertyValue<Il2CppString*>(text, "text"));
        // Faster to convert the old text, use c++ strings, convert it back then it is to use C# string.Concat (although only marginally)
        judgment_cs = il2cpp_utils::createcsstr(best.tokenizedText->Join() + "\n" + to_utf8(csstrtostr(judgment_cs)));
    }
    else if (config.displayMode == DISPLAY_MODE_IMAGEONLY) {
        // Skip
        return true;
    } else if (config.displayMode == DISPLAY_MODE_IMAGEANDTEXT) {
        RET_F_UNLESS(best.tokenizedText);
        judgment_cs = parseFormattedText(best, beforeCut, afterCut, cutDistance);
    }

    // Runtime invoke set_richText to true
    RET_F_UNLESS(il2cpp_utils::SetPropertyValue(text, "richText", true));

    // Runtime invoke set_enableWordWrapping false
    RET_F_UNLESS(il2cpp_utils::SetPropertyValue(text, "enableWordWrapping", false));

    // Runtime invoke set_overflowMode to OverflowModes.Overflow (0)
    RET_F_UNLESS(il2cpp_utils::SetPropertyValue(text, "overflowMode", 0));

    // Set text if it is not null
    RET_F_UNLESS(judgment_cs);
    RET_F_UNLESS(il2cpp_utils::SetPropertyValue(text, "text", judgment_cs));
    return true;
}

bool HSV::addImage(Il2CppObject* flyingScoreEffect, judgment best, int beforeCut, int afterCut, int cutDistance) {
    getLogger().debug("Adding image...");
    if (config.displayMode == DISPLAY_MODE_IMAGEONLY) {
        RET_F_UNLESS(best.imagePath);
    } else if (config.displayMode == DISPLAY_MODE_IMAGEANDTEXT) {
        if (!best.imagePath) {
            // Simply use fallback text if no image is provided
            return true;
        }
    } else {
        // Don't display an image
        return true;
    }
    static auto spriteRendererType = il2cpp_utils::GetSystemType("UnityEngine", "SpriteRenderer");
    RET_F_UNLESS(spriteRendererType);
    Il2CppObject* existing = RET_F_UNLESS(il2cpp_utils::RunMethod(flyingScoreEffect, "GetComponent", spriteRendererType));
    if (existing) {
        // Already displaying an image, no need to fail
        getLogger().debug("found sprite renderer: %p", existing);
    } else {
        // SpriteRenderer spriteRender = flyingScoreEffect.gameObject.AddComponent(typeof(SpriteRenderer));
        auto go = RET_F_UNLESS(il2cpp_utils::GetPropertyValue(flyingScoreEffect, "gameObject").value_or(nullptr));
        existing = RET_F_UNLESS(il2cpp_utils::RunMethod(go, "AddComponent", spriteRendererType).value_or(nullptr));
        getLogger().debug("Created sprite renderer: %p", existing);
    }
    // Get texture
    auto sprite = spriteManager.GetSprite(*best.imagePath).value_or(nullptr);
    if (sprite) {
        getLogger().debug("Found sprite!");
        // spriteRenderer.set_sprite(sprite);
        RET_F_UNLESS(il2cpp_utils::SetPropertyValue(existing, "sprite", sprite));
        getLogger().debug("Set sprite!");
        if (best.color) {
            // spriteRenderer.set_color(color);
            RET_F_UNLESS(il2cpp_utils::SetPropertyValue(existing, "color", *best.color));
        } else {
            // Use default color instead of last color
            RET_F_UNLESS(il2cpp_utils::SetPropertyValue(existing, "color", (Color){1.0f, 1.0f, 1.0f, 1.0f}));
        }
    }
    getLogger().debug("Adding image complete!");
    // TODO: Add segment images here
    return true;
}

bool HSV::addAudio(Il2CppObject* textObj, judgment toPlay) {
    // Check to see if we have an AudioSource already.
    // If we do, that means we already started our audio, so don't make another
    // If we don't make one and play audio on it.
    if (!toPlay.soundPath) {
        // No need to fail with logs if we didn't even want to add a sound
        return true;
    }
    static auto audioSourceType = il2cpp_utils::GetSystemType("UnityEngine", "AudioSource");
    RET_F_UNLESS(audioSourceType);
    Il2CppObject* existing = RET_F_UNLESS(il2cpp_utils::RunMethod(textObj, "GetComponent", audioSourceType));
    if (existing) {
        // Already playing a sound, no need to fail
        getLogger().debug("Existing AudioSource: %p", existing);
    } else {
        auto go = RET_F_UNLESS(il2cpp_utils::GetPropertyValue(textObj, "gameObject").value_or(nullptr));
        existing = RET_F_UNLESS(il2cpp_utils::RunMethod(go, "AddComponent", audioSourceType).value_or(nullptr));
        getLogger().debug("Created AudioSource: %p", existing);
    }
    // Get audio clip
    auto clip = audioManager.GetAudioClip(*toPlay.soundPath).value_or(nullptr);
    if (clip) {
        RET_F_UNLESS(il2cpp_utils::RunMethod(existing, "PlayOneShot", clip, toPlay.soundVolume.value_or(1.0f)));
    }
    return true;
}

void HSV::checkJudgments(Il2CppObject* flyingScoreEffect, int beforeCut, int afterCut, int cutDistance) {
    getLogger().debug("Checking judgments!");
    if (!configValid) {
        return;
    }
    auto bestIndex = getBestJudgment(config.judgments, beforeCut + afterCut + cutDistance);
    RET_V_UNLESS(bestIndex);
    getLogger().debug("Index: %d", *bestIndex);
    auto best = config.judgments[*bestIndex];

    getLogger().debug("Adding color");
    if (!addColor(flyingScoreEffect, *bestIndex, beforeCut + afterCut + cutDistance)) {
        getLogger().error("Failed to add color!");
    }

    getLogger().debug("Adding image");
    if (!addImage(flyingScoreEffect, best, beforeCut, afterCut, cutDistance)) {
        getLogger().error("Failed to add image!");
    }

    getLogger().debug("Adding text");
    if (!addText(flyingScoreEffect, best, beforeCut, afterCut, cutDistance)) {
        getLogger().error("Failed to add text!");
    }

    getLogger().debug("Adding sound");
    if (!addAudio(flyingScoreEffect, best)) {
        getLogger().error("Failed to add audio!");
    }
    getLogger().debug("Complete with judging!");
}

Il2CppString* HSV::parseFormattedText(judgment best, int beforeCut, int afterCut, int cutDistance) {
    // best.tokenizedText must be non-optional when this function is called.
    std::stringstream ststr;
    getLogger().debug("%d, %d, %d", beforeCut, afterCut, cutDistance);
    bool isPercent = false;
    // TODO: Can make this EVEN FASTER by getting a list of indices of where the %'s are ONCE
    // Tokenize this, cache text locations AOT
    // And then replacing the corresponding indices with them as we iterate
    // For each of the vectors in the tokenized text, we would like to first check to ensure there are tokens for that type
    // If there are, we convert and pass in the string.
    auto& tokens = *best.tokenizedText;
    // Standard
    if (tokens.get_beforeCutTokens_size() > 0) {
        tokens.set_beforeCut(std::to_string(beforeCut));
    }
    if (tokens.get_cutDistanceTokens_size() > 0) {
        tokens.set_cutDistance(std::to_string(cutDistance));
    }
    if (tokens.get_afterCutTokens_size() > 0) {
        tokens.set_afterCut(std::to_string(afterCut));
    }
    // Segments
    if (tokens.get_beforeCutSegmentTokens_size() > 0) {
        std::string val = "";
        auto bestSeg = getBestSegment(config.beforeCutAngleJudgments, beforeCut);
        if (bestSeg) {
            val = bestSeg->text.value_or("");
        }
        tokens.set_beforeCutSegment(val);
    }
    if (tokens.get_cutDistanceSegmentTokens_size() > 0) {
        std::string val = "";
        auto bestSeg = getBestSegment(config.accuracyJudgments, cutDistance);
        if (bestSeg) {
            val = bestSeg->text.value_or("");
        }
        tokens.set_cutDistanceSegment(val);
    }
    if (tokens.get_afterCutSegmentTokens_size() > 0) {
        std::string val = "";
        auto bestSeg = getBestSegment(config.afterCutAngleJudgments, afterCut);
        if (bestSeg) {
            val = bestSeg->text.value_or("");
        }
        tokens.set_afterCutSegment(val);
    }
    if (tokens.get_scoreTokens_size() > 0) {
        tokens.set_score(std::to_string(beforeCut + cutDistance + afterCut));
    }
    if (tokens.get_percentTokens_size() > 0) {
        // Use 115.0 as max score
        tokens.set_percent(string_format("%.2f", (beforeCut + cutDistance + afterCut) / 115.0f * 100.0));
    }
    return il2cpp_utils::createcsstr(tokens.Join());
}