#include "../include/main.hpp"
#include "../include/config.hpp"
#include <ctime>

#define CONFIG_BACKUP_PATH CONFIG_PATH "HitScoreVisualizer_backup.json"

static HSVConfig config;

// Helper functions
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
    if (size == 0) {
        return "";
    }
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
        replace = str_class->methods[96];
        concat = str_class->methods[112];
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
    Il2CppString* judgement_cs = nullptr;

    if (config.displayMode == DISPLAY_MODE_FORMAT) {
        std::stringstream ststr;
        bool isPercent = false;
        for (auto itr = best.text.begin(); itr != best.text.end(); ++itr) {
            auto current = *itr;
            if (isPercent) {
                // If the last character was a %
                // For literal scores to sprintf
                char buffer[7];
                // For pointers to judgement text
                const char* out = nullptr;
                switch (current) {
                    case 'b':
                        sprintf(buffer, "%d", beforeCut);
                        break;
                    case 'c':
                        sprintf(buffer, "%d", cutDistance);
                        break;
                    case 'a':
                        sprintf(buffer, "%d", afterCut);
                        break;
                    case 'B':
                        out = getBestSegment(config.beforeCutAngleJudgements, beforeCut);
                        break;
                    case 'C':
                        out = getBestSegment(config.accuracyJudgements, cutDistance);
                        break;
                    case 'A':
                        out = getBestSegment(config.afterCutAngleJudgements, afterCut);
                        break;
                    case 's':
                        sprintf(buffer, "%d", score);
                        break;
                    case 'p':
                        sprintf(buffer, "%.2f", score / 115.0 * 100.0);
                        break;
                    case 'n':
                        sprintf(buffer, "\n");
                        break;
                    case '%':
                    default:
                        sprintf(buffer, "%%%c", current);
                }
                if (out) {
                    ststr << out;
                } else {
                    ststr << buffer;
                }
                isPercent = false;
                continue;
            }
            if (current == '%' && !isPercent) {
                isPercent = true;
            } else {
                ststr.put(current);
            }
        }
        judgement_cs = il2cpp_utils::createcsstr(ststr.str().data());
    } else if (config.displayMode == DISPLAY_MODE_NUMERIC) {
        // Numeric display ONLY
        judgement_cs = old_text;
    } else if (config.displayMode == DISPLAY_MODE_SCOREONTOP) {
        // Score on top
        // Add newline
        judgement_cs = concatBuffer(concatBuffer(old_text, "\n"), best.text.data());
    } else {
        // Text on top
        judgement_cs = il2cpp_utils::createcsstr(best.text.data());
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
    if (config.useSeasonalThemes) {
        // Check season
        time_t now = std::time(nullptr);
        tm* currentTm = std::localtime(&now);
        log(DEBUG, "Current datetime: (%i/%i)", currentTm->tm_mon, currentTm->tm_mday);
        // Christmas is 1 + 11 month, 23 - 25 day
        if (currentTm->tm_mon == 11 && (currentTm->tm_mday >= 23 && currentTm->tm_mday <= 24)) {
            if (config.backupBeforeSeason) {
                log(DEBUG, "Backing up config before seasonal swap...");
                // Before we backup, we must first ensure we have written out the correct info
                // So we don't have to fail to parse it again in the future
                config.WriteToConfig(Configuration::config);
                ConfigHelper::BackupConfig(Configuration::config, CONFIG_BACKUP_PATH);
            }
            log(DEBUG, "Setting to Christmas config!");
            config.SetToChristmas();
        } else {
            if (config.type != CONFIG_TYPE_STANDARD) {
                // Otherwise, set to standard - iff config.restoreAfterSeason is set and there is a viable backup
                if (config.restoreAfterSeason && fileexists(CONFIG_BACKUP_PATH)) {
                    log(DEBUG, "Restoring config from: %s", CONFIG_BACKUP_PATH);
                    ConfigHelper::RestoreConfig(CONFIG_BACKUP_PATH);
                    config = ConfigHelper::LoadConfig(Configuration::config);
                    // Delete the old path to ensure we don't load from it again
                    deletefile(CONFIG_BACKUP_PATH);
                } else if (config.restoreAfterSeason) {
                    // If there isn't a viable backup, but we want to restore, set to default
                    log(DEBUG, "Setting config to default from type: %i", config.type);
                    config.SetToDefault();
                }
            }
        }
        log(DEBUG, "Writing Config to JSON file!");
        config.WriteToConfig(Configuration::config);
        log(DEBUG, "Writing Config JSON to file!");
        Configuration::Write();
    }
}

void loadConfig() {
    log(INFO, "Loading Configuration...");
    Configuration::Load();
    config = ConfigHelper::LoadConfig(Configuration::config);
    if (config.VersionLessThanEqual(2, 3, 0) && config.type == CONFIG_TYPE_CHRISTMAS) {
        // Let's just auto fix everyone's configs that are less than 2.3.0 and are of Christmas type
        log(DEBUG, "Setting to default because version <= 2.3.0! Actual: %i.%i.%i", config.majorVersion, config.minorVersion, config.patchVersion);
        config.SetToDefault();
        config.WriteToConfig(Configuration::config);
    }
    log(INFO, "Loaded Configuration! Metadata: type: %i, useSeasonalThemes: %c, restoreAfterSeason: %c", config.type, config.useSeasonalThemes ? 't' : 'f', config.restoreAfterSeason ? 't' : 'f');
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