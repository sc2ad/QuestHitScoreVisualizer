#include "../include/main.hpp"
#include "../include/config.hpp"
#include <ctime>

#define CONFIG_BACKUP_PATH CONFIG_PATH "HitScoreVisualizer_backup.json"

static HSVConfig config;

// Helper functions
Il2CppString* replaceBuffer(Il2CppString* q, std::string_view left, std::string_view right) {
    Il2CppString* outp;
    if (il2cpp_utils::RunMethod(&outp, q, replace, il2cpp_utils::createcsstr(left), il2cpp_utils::createcsstr(right))) {
        return outp;
    }
    return nullptr;
}
Il2CppString* concatBuffer(Il2CppString* left, std::string_view right) {
    Il2CppString* outp;
    if (il2cpp_utils::RunMethod(&outp, nullptr, concat, left, il2cpp_utils::createcsstr(right))) {
        return outp;
    }
    return nullptr;
}
Il2CppString* concatBuffer(Il2CppString* left, Il2CppString* right) {
    Il2CppString* outp;
    if (il2cpp_utils::RunMethod(&outp, nullptr, concat, left, right)) {
        return outp;
    }
    return nullptr;
}
const char* getBestSegment(std::vector<segment>& segments, int comparison) {
    auto size = segments.size();
    auto& best = segments[size - 1];
    for (int i = size - 2; i >= 0; i--) {
        if (segments[i].threshold > comparison) {
            break;
        }
        best = segments[i];
    }
    return best.text;
}
void checkJudgements(Il2CppObject* flyingScoreEffect, int beforeCut, int afterCut, int cutDistance) {
    static auto tmp_class = il2cpp_utils::GetClassFromName("TMPro", "TMP_Text");
    static auto set_richText = il2cpp_utils::GetMethod(tmp_class, "set_richText", 1);
    static auto set_enableWordWrapping = il2cpp_utils::GetMethod(tmp_class, "set_enableWordWrapping", 1);
    static auto set_overflowMode = il2cpp_utils::GetMethod(tmp_class, "set_overflowMode", 1);
    static auto get_text = il2cpp_utils::GetMethod(tmp_class, "get_text", 0);
    static auto set_text = il2cpp_utils::GetMethod(tmp_class, "set_text", 1);
    static auto str_class = il2cpp_utils::GetClassFromName("System", "String");
    // TODO FIX YUCKY HACK
    if (replace == nullptr) {
        replace = str_class->methods[97];
        concat = str_class->methods[113];
    }
    static auto length = config.judgements.size();
    int score = beforeCut + afterCut + cutDistance;
    auto& best = config.judgements[length - 1];
    for (int i = length - 2; i >= 0; i--) {
        if (config.judgements[i].threshold > score) {
            break;
        }
        best = config.judgements[i];
    }

    // TODO Add fading
    Color color;
    il2cpp_utils::GetFieldValue(&color, flyingScoreEffect, "_color");
    color.r = best.color[0];
    color.g = best.color[1];
    color.b = best.color[2];
    color.a = best.color[3];
    il2cpp_utils::SetFieldValue(flyingScoreEffect, "_color", &color);

    Il2CppObject* text;
    il2cpp_utils::GetFieldValue(&text, flyingScoreEffect, "_text");

    // Runtime invoke set_richText to true
    bool set_to = true;
    il2cpp_utils::RunMethod(text, set_richText, &set_to);

    // Runtime invoke set_enableWordWrapping false
    set_to = false;
    il2cpp_utils::RunMethod(text, set_enableWordWrapping, &set_to);

    // Runtime invoke set_overflowMode false
    il2cpp_utils::RunMethod(text, set_overflowMode, &set_to);

    // Get Text
    Il2CppString* old_text;
    il2cpp_utils::RunMethod(&old_text, text, get_text);
    Il2CppString* judgement_cs = il2cpp_utils::createcsstr(best.text);

    if (config.displayMode == DISPLAY_MODE_FORMAT) {
        // THIS IS VERY INEFFICIENT AND SLOW BUT SHOULD WORK!
        char buffer[4]; // Max length for score buffers is 3
        // %b
        sprintf(buffer, "%d", beforeCut);
        judgement_cs = replaceBuffer(judgement_cs, "%b", buffer);
        // %c
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%d", cutDistance);
        judgement_cs = replaceBuffer(judgement_cs, "%c", buffer);
        // %a
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%d", afterCut);
        judgement_cs = replaceBuffer(judgement_cs, "%a", buffer);
        // %B
        const char* bestBeforeSeg = getBestSegment(config.beforeCutAngleJudgements, beforeCut);
        judgement_cs = replaceBuffer(judgement_cs, "%B", bestBeforeSeg);
        // %C
        const char* bestCutAcc = getBestSegment(config.accuracyJudgements, cutDistance);
        judgement_cs = replaceBuffer(judgement_cs, "%C", bestCutAcc);
        // %A
        const char* bestAfterSeg = getBestSegment(config.afterCutAngleJudgements, afterCut);
        judgement_cs = replaceBuffer(judgement_cs, "%A", bestAfterSeg);
        // %s
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%d", score);
        judgement_cs = replaceBuffer(judgement_cs, "%s", buffer);
        // %p
        char percentBuff[7]; // 6 is upper bound for 100.00 percent
        sprintf(percentBuff, "%.2f", score / 115.0 * 100.0);
        judgement_cs = replaceBuffer(judgement_cs, "%p", percentBuff);
        // %%
        judgement_cs = replaceBuffer(judgement_cs, "%%", "%");
        // %n
        judgement_cs = replaceBuffer(judgement_cs, "%n", "\n");
    } else if (config.displayMode == DISPLAY_MODE_NUMERIC) {
        // Numeric display ONLY
        judgement_cs = old_text;
    } else if (config.displayMode == DISPLAY_MODE_SCOREONTOP) {
        // Score on top
        // Add newline
        judgement_cs = concatBuffer(concatBuffer(old_text, "\n"), best.text);
    } else {
        // Text on top
        log(DEBUG, "Displaying judgement text on top!");
        log(DEBUG, "Old Text: %s", to_utf8(csstrtostr(old_text)).c_str());
        auto temp = concatBuffer(judgement_cs, "\n");
        log(DEBUG, "New temp text: %s", to_utf8(csstrtostr(temp)).c_str());
        // Add newline
        judgement_cs = concatBuffer(temp, old_text);
    }
    il2cpp_utils::RunMethod(text, set_text, judgement_cs);
}
// Checks season, sets config to correct season
void setConfigToCurrentSeason() {
    if (config.useSeasonalThemes && config.type != CONFIG_TYPE_CHRISTMAS) {
        // If not Christmas
        time_t now = std::time(nullptr);
        tm* currentTm = std::localtime(&now);
        if (currentTm->tm_mon == 12 && (currentTm->tm_mday >= 23 && currentTm->tm_mday <= 25)) {
            if (config.backupBeforeSeason)
                ConfigHelper::BackupConfig(Configuration::config, CONFIG_BACKUP_PATH);
            config.SetToChristmas();
        } else {
            // Otherwise, set to standard
            if (config.restoreAfterSeason) {
                ConfigHelper::RestoreConfig(CONFIG_BACKUP_PATH);
                // Delete the old path to ensure we don't load from it again
                deletefile(CONFIG_BACKUP_PATH);
            } else {
                config.SetToDefault();
            }
        }
        config.WriteToConfig(Configuration::config);
        Configuration::Write();
    }
}

void loadConfig() {
    log(INFO, "Loading Configuration...");
    Configuration::Load();
    config = ConfigHelper::LoadConfig(Configuration::config);
    log(INFO, "Loaded Configuration!");
    setConfigToCurrentSeason();
    log(INFO, "Set Configuration to current season! Type: %i", config.type);
}
// Install hooks
extern "C" void load() {
    loadConfig();
    log(INFO, "Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(FlyingScoreEffect_HandleSaberSwingRatingCounterDidChangeEvent, il2cpp_utils::GetMethod("", "FlyingScoreEffect", "HandleSaberSwingRatingCounterDidChangeEvent", 2));
    log(INFO, "Installed hooks!");
}