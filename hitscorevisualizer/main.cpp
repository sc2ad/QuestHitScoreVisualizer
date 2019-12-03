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
#include <utility>
#include <type_traits>

#include "../beatsaber-hook/shared/inline-hook/inlineHook.h"

#include "../beatsaber-hook/shared/utils/utils.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include "../beatsaber-hook/rapidjson/include/rapidjson/document.h"
#include "../beatsaber-hook/rapidjson/include/rapidjson/allocators.h"
#include "../beatsaber-hook/shared/utils/config-utils.hpp"
#include "../beatsaber-hook/shared/utils/mod-checks.hpp"
#include "main.h"

static void createdefaultjson(ConfigDocument& config, rapidjson::Document::AllocatorType& allocator);

// TODO: figure out some way for configs to have default values WITHOUT having to write them to the config file
static void CheckRegenConfig(ConfigDocument& config) {
    if (!config.HasMember("regenerateConfig") || config["regenerateConfig"].GetBool()) {
        log(WARNING, "Regenerating config!");
        config.SetObject();
        auto& allocator = config.GetAllocator();
        createdefaultjson(config, allocator);
        config.AddMember("regenerateConfig", rapidjson::Value(true), allocator);
        log(DEBUG, "Attempting to write config");
        Configuration::Write();
        log(INFO, "Config regeneration complete!");
    } else {
        log(INFO, "Not regnerating config.");
    }
}

static auto& config_doc = Configuration::config;
static Config config;

static void InitConfig() {
    Configuration::Load();
    CheckRegenConfig(config_doc);
}

static void ReloadConfig() {
    Configuration::Reload();
    CheckRegenConfig(config_doc);
}

static void addJudgement(rapidjson::Document::AllocatorType& alloc, rapidjson::Document::ValueType& arr, int thresh, std::string_view text, std::vector<float> colors, bool fade = false) {
    auto v = ConfigValue(rapidjson::kObjectType).GetObject();
    v.AddMember(ConfigValue("threshold"), ConfigValue(thresh), alloc);
    v.AddMember("threshold", ConfigValue(thresh), alloc);
    v.AddMember("text", ConfigValue(text.data(), text.length()), alloc);
    auto color = ConfigValue(rapidjson::kArrayType).GetArray();
    for (int i = 0; i < 4; i++) {
        color.PushBack(ConfigValue(colors[i]), alloc);
    }
    v.AddMember("color", color, alloc);
    v.AddMember("fade", rapidjson::Value(fade), alloc);
    arr.SetArray();
    arr.PushBack(v, alloc);
}

static void addSegment(rapidjson::Document::AllocatorType& alloc, rapidjson::Document::ValueType& arr, int thresh, std::string_view text) {
    auto v = rapidjson::Value(rapidjson::kObjectType);
    v.AddMember("threshold", rapidjson::Value(thresh), alloc);
    v.AddMember("text", rapidjson::Value(text.data(), text.length()), alloc);
    arr.SetArray();
    arr.PushBack(v, alloc);
}

static void createdefaultjson(ConfigDocument& config, rapidjson::Document::AllocatorType& allocator) {
    log(DEBUG, "Attempting to create default config");

    config.AddMember("majorVersion", rapidjson::Value(2), allocator);
    config.AddMember("minorVersion", rapidjson::Value(2), allocator);
    config.AddMember("patchVersion", rapidjson::Value(0), allocator);
    log(DEBUG, "Added versions!");
    auto judgements = rapidjson::Value(rapidjson::kArrayType);
    log(DEBUG, "About to add judgements...");
    addJudgement(allocator, judgements, 115, "%BFantastic%A%n%s", {1.0, 1.0, 1.0, 1.0});
    addJudgement(allocator, judgements, 101, "<size=80%>%BExcellent%A</size>%n%s", {0.0, 1.0, 0.0, 1.0});
    addJudgement(allocator, judgements, 90, "<size=80%>%BGreat%A</size>%n%s", {1.0, 0.980392158, 0.0, 1.0});
    addJudgement(allocator, judgements, 80, "<size=80%>%BGood%A</size>%n%s", {1.0, 0.6, 0.0, 1.0}, true);
    addJudgement(allocator, judgements, 60, "<size=80%>%BDecent%A</size>%n%s", {1.0, 0.0, 0.0, 1.0}, true);
    addJudgement(allocator, judgements, 0, "<size=80%>%BWay Off%A</size>%n%s", {0.5, 0.0, 0.0, 1.0}, true);
    config.AddMember("judgements", judgements, allocator);
    log(DEBUG, "Added judgements!");
    auto beforeCutAngleJudgements = rapidjson::Value(rapidjson::kArrayType);
    addSegment(allocator, beforeCutAngleJudgements, 70, "+");
    addSegment(allocator, beforeCutAngleJudgements, 0, " ");
    config.AddMember("beforeCutAngleJudgements", beforeCutAngleJudgements, allocator);
    log(DEBUG, "Added angle judgements!");
    auto accuracyJudgements = rapidjson::Value(rapidjson::kArrayType);
    addSegment(allocator, accuracyJudgements, 15, "+");
    addSegment(allocator, accuracyJudgements, 0, " ");
    config.AddMember("accuracyJudgements", accuracyJudgements, allocator);
    log(DEBUG, "Added accuracy judgements!");
    auto afterCutAngleJudgements = rapidjson::Value(rapidjson::kArrayType);
    addSegment(allocator, afterCutAngleJudgements, 30, "+");
    addSegment(allocator, afterCutAngleJudgements, 0, " ");
    config.AddMember("afterCutAngleJudgements", afterCutAngleJudgements, allocator);
    log(DEBUG, "Added after angle judgements!");
    // std::string filename = getconfigpath();

    // int r = writefile(filename.c_str(), js);
    // if (r == 0) {
    //     log(INFO, "CREATED DEFAULT JSON FILE AT PATH: %s", filename.c_str());
    // }
    // else if (r == WRITE_ERROR_COULD_NOT_MAKE_FILE) {
    //     log(INFO, "COULD NOT MAKE DEFAULT JSON FILE AT PATH: %s", filename.c_str());
    // }
}

static bool createjudgements(rapidjson::Document::ValueType& arrayValue) {
    int index = 0;
    // config.judgements.clear();
    auto arr = arrayValue.GetArray();
    config.judgements.reserve(arr.Size());
    config.judgements.assign(arr.Size(), judgement());
    for (auto& v : arr) {
        if (!v.IsObject()) {
            // ERROR
            log(ERROR, "judgements.item not Object!");
            return false;
        }
        // config.judgements.push_back(judgement());
        for (auto jitr = v.GetObject().MemberBegin(); jitr != v.GetObject().MemberEnd(); jitr++) {
            if (strcmp(jitr->name.GetString(), "threshold") == 0) {
                if (!jitr->value.IsInt()) {
                    // ERROR
                    log(ERROR, "judgements.threshold not Int!");
                    return false;
                }
                config.judgements[index].threshold = jitr->value.GetInt();
            }
            else if (strcmp(jitr->name.GetString(), "text") == 0) {
                if (!jitr->value.IsString()) {
                    // ERROR
                    log(ERROR, "judgements.text not String!");
                    return false;
                }
                config.judgements[index].text = jitr->value.GetString();
            }
            else if (strcmp(jitr->name.GetString(), "color") == 0) {
                if (!jitr->value.IsArray()) {
                    // ERROR
                    log(ERROR, "judgements.color not Array!");
                    return false;
                }
                int ci = 0;
                for (auto& c : jitr->value.GetArray()) {
                    if (!c.IsFloat()) {
                        // ERROR
                        log(ERROR, "judgements.color.item not Float!");
                        return false;
                    }
                    switch (ci) {
                        case 0: 
                            config.judgements[index].r = c.GetFloat();
                            break;
                        case 1:
                            config.judgements[index].g = c.GetFloat();
                            break;
                        case 2:
                            config.judgements[index].b = c.GetFloat();
                            break;
                        case 3:
                            config.judgements[index].a = c.GetFloat();
                            break;
                    }
                    ci++;
                }
            }
            else if (strcmp(jitr->name.GetString(), "fade") == 0) {
                if (!jitr->value.IsBool()) {
                    // ERROR
                    log(ERROR, "judgements.fade not Bool!");
                    return false;
                }
                config.judgements[index].fade = jitr->value.GetBool();
            }
        }
        index++;
    }
    return true;
}

static bool createjudgementsegments(std::vector<judgement_segment> &vec, rapidjson::GenericArray<false, ConfigValue> arr) {
    int index = 0;
    log(DEBUG, "Segments array has size: %d", arr.Size());
    for (auto& v : arr) {
        if (!v.IsObject()) {
            // ERROR
            log(ERROR, "judgementsegments.item not Int!");
            return false;
        }
        log(DEBUG, "Adding segment...");
        // vec->push_back(judgement_segment());
        for (auto jitr = v.GetObject().MemberBegin(); jitr != v.GetObject().MemberEnd(); jitr++) {
            if (strcmp(jitr->name.GetString(), "threshold") == 0) {
                if (!jitr->value.IsInt()) {
                    // ERROR
                    log(ERROR, "judgementsegments.threshold not Int!");
                    return false;
                }
                vec[index].threshold = jitr->value.GetInt();
            }
            else if (strcmp(jitr->name.GetString(), "text") == 0) {
                if (!jitr->value.IsString()) {
                    // ERROR
                    log(ERROR, "judgementsegments.text not String!");
                    return false;
                }
                vec[index].text = jitr->value.GetString();
            }
        }
        index++;
    }
    return true;
}

// Returns 0 on success, -1 on failure, but don't create default JSON, -2 on failure and do create JSON
static int loadjudgements() {
    log(DEBUG, "Loading judgements...");
    Configuration::Load();
    ConfigDocument& config_doc = Configuration::config;

    // Two approach ideas:
    // 1. Iterate over all members
    // 2. Call FindMember a bunch of times
    // 1:
    if (config_doc.HasMember("useJson")) {
        if (!config_doc["useJson"].IsBool()) {
            config_doc["useJson"].SetBool(true);
            Configuration::Write();
        }
        if (!config_doc["useJson"].GetBool()) {
            // Exit without parsing the JSON
            log(INFO, "useJson is false, loading candy crush config!");
            return -1;
        }
    }
    for (auto itr = config_doc.MemberBegin(); itr != config_doc.MemberEnd(); itr++) {
        if (strcmp(itr->name.GetString(), "majorVersion") == 0) {
            if (!itr->value.IsInt()) {
                // ERROR
                log(ERROR, "majorVersion not Int!");
                return -2;
            }
            config.majorVersion = itr->value.GetInt();
        }
        else if (strcmp(itr->name.GetString(), "minorVersion") == 0) {
            if (!itr->value.IsInt()) {
                // ERROR
                log(ERROR, "minorVersion not Int!");
                return -2;
            }
            config.minorVersion = itr->value.GetInt();
        }
        else if (strcmp(itr->name.GetString(), "patchVersion") == 0) {
            if (!itr->value.IsInt()) {
                // ERROR
                log(ERROR, "patchVersion not Int!");
                return -2;
            }
            config.patchVersion = itr->value.GetInt();
        }
        else if (strcmp(itr->name.GetString(), "displayMode") == 0) {
            if (!itr->value.IsString()) {
                // ERROR
                log(ERROR, "displayMode not String!");
                return -2;
            }
            log(DEBUG, "DisplayMode: %s", itr->value.GetString());
            if (strcmp(itr->value.GetString(), "format") == 0) {
                config.displayMode = DISPLAY_MODE_FORMAT;
            }
            else if (strcmp(itr->value.GetString(), "numeric") == 0) {
                config.displayMode = DISPLAY_MODE_NUMERIC;
            }
            else if (strcmp(itr->value.GetString(), "scoreOnTop") == 0) {
                config.displayMode = DISPLAY_MODE_SCOREONTOP;
            }
            else if (strcmp(itr->value.GetString(), "textOnly") == 0) {
                config.displayMode = DISPLAY_MODE_TEXTONLY;
            }
            else if (strcmp(itr->value.GetString(), "textOnTop") == 0) {
                config.displayMode = DISPLAY_MODE_TEXTONTOP;
            }
            else {
                log(ERROR, "displayMode unknown: %s", itr->value.GetString());
                return -2;
            }
        }
        else if (strcmp(itr->name.GetString(), "judgments") == 0) {
            if (!itr->value.IsArray()) {
                // ERROR
                log(ERROR, "judgements not Array!");
                return -2;
            }
            log(DEBUG, "Creating Judgements!");
            if (!createjudgements(itr->value)) {
                // ERROR
                return -2;
            }
        }
        else if (strcmp(itr->name.GetString(), "beforeCutAngleJudgments") == 0) {
            if (!itr->value.IsArray()) {
                // ERROR
                log(ERROR, "beforeCutAngleJudgments not Array!");
                return -2;
            }
            log(DEBUG, "Creating beforeCutAngleJudgments!");
            config.beforeCutAngleJudgements.reserve(itr->value.GetArray().Size());
            config.beforeCutAngleJudgements.assign(itr->value.GetArray().Size(), judgement_segment());
            if (!createjudgementsegments(config.beforeCutAngleJudgements, itr->value.GetArray())) {
                // ERROR
                log(ERROR, "beforeCutAngleJudgments ERROR!");
                return -2;
            }
        }
        else if (strcmp(itr->name.GetString(), "accuracyJudgments") == 0) {
            if (!itr->value.IsArray()) {
                // ERROR
                log(ERROR, "accuracyJudgments not Array!");
                return -2;
            }
            log(DEBUG, "Creating accuracyJudgments!");
            config.accuracyJudgements.reserve(itr->value.GetArray().Size());
            config.accuracyJudgements.assign(itr->value.GetArray().Size(), judgement_segment());
            if (!createjudgementsegments(config.accuracyJudgements, itr->value.GetArray())) {
                // ERROR
                log(ERROR, "accuracyJudgments ERROR!");
                return -2;
            }
        }
        else if (strcmp(itr->name.GetString(), "afterCutAngleJudgments") == 0) {
            if (!itr->value.IsArray()) {
                // ERROR
                log(ERROR, "afterCutAngleJudgments not Array!");
                return -2;
            }
            log(DEBUG, "Creating afterCutAngleJudgments!");
            config.afterCutAngleJudgements.reserve(itr->value.GetArray().Size());
            config.afterCutAngleJudgements.assign(itr->value.GetArray().Size(), judgement_segment());
            if (!createjudgementsegments(config.afterCutAngleJudgements, itr->value.GetArray())) {
                // ERROR
                log(ERROR, "afterCutAngleJudgments ERROR!");
                return -2;
            }
        }
    }
    if (config.judgements.size() < 1 || config.accuracyJudgements.size() < 1 || config.beforeCutAngleJudgements.size() < 1 || config.afterCutAngleJudgements.size() < 1) {
        // DID NOT LOAD JUDGEMENTS
        log(INFO, "Config Judgements Size: %lu", config.judgements.size());
        log(INFO, "Config accuracyJudgements Size: %lu", config.accuracyJudgements.size());
        log(INFO, "Config beforeCutAngleJudgements Size: %lu", config.beforeCutAngleJudgements.size());
        log(INFO, "Config afterCutAngleJudgements: %lu", config.afterCutAngleJudgements.size());
        log(INFO, "Did not load all required information from JSON. Empty config file?");
        return -2;
    }
    if (config.majorVersion < 2 || (config.majorVersion == 2 && config.minorVersion < 2) || (config.majorVersion == 2 && config.minorVersion == 2 && config.patchVersion < 0)) {
        // VERSION ERROR
        log(INFO, "Version mismatch! Version is: %d.%d.%d but should be >= 2.2.0!", config.majorVersion, config.minorVersion, config.patchVersion);
        return -1;
    }
    return 0;
}

static bool loadall() {
    log(INFO, "Loading Configuration...");
    Configuration::Load();
    log(INFO, "Loaded Configuration!");
    log(DEBUG, "Created Initial Config Object, should no longer be null!");
    int r = loadjudgements();
    if (r == -2) {
        InitConfig();
        log(INFO, "Loading default JSON...");
        r = loadjudgements();
    } if (r == -1) {
        InitConfig();
        log(INFO, "Loading candy crush config");
        // createdefault();
        r = loadjudgements();
    } if (r == -2) {
        log(CRITICAL, "COULD NOT LOAD DEFAULT JSON!");
        // createdefault();
        exit(1);
    }
    if (r == 0) {
        log(INFO, "Successfully loaded judgements from JSON!");
    }
    log(DEBUG, "Sizes: %lu, %lu, %lu, %lu", config.judgements.size(), config.beforeCutAngleJudgements.size(), config.accuracyJudgements.size(), config.afterCutAngleJudgements.size());
    return r == 0;
}

static const char* getBestSegment(std::vector<judgement_segment> segments, int comparison) {
    judgement_segment best = segments[segments.size() - 1];
    for (int i = segments.size() - 2; i >= 0; i--) {
        if (segments[i].threshold > comparison) {
            break;
        }
        best = segments[i];
    }
    return best.text;
}


static const MethodInfo* replace = nullptr;
static const MethodInfo* concat = nullptr;

static Il2CppString* replaceBuffer(Il2CppString* q, std::string_view left, std::string_view right) {
    void* args[] = {reinterpret_cast<void*>(il2cpp_utils::createcsstr(left)), reinterpret_cast<void*>(il2cpp_utils::createcsstr(right))};
    Il2CppException* exp;
    Il2CppString* judgement_cs = (Il2CppString*)il2cpp_functions::runtime_invoke(replace, q, args, &exp);
    if (exp) {
        // ERROR VIA EXCEPTION
        log(ERROR, "%s", il2cpp_utils::ExceptionToString(exp).c_str());
        return nullptr;
    }
    log(DEBUG, "String replacement with orig: %s old: %s new: %s final: %s", to_utf8(csstrtostr(q)).c_str(), left.data(), right.data(), to_utf8(csstrtostr(judgement_cs)).c_str());
    return judgement_cs;
}

static Il2CppString* concatBuffer(Il2CppString* left, std::string_view right) {
    void* args[] = {reinterpret_cast<void*>(left), reinterpret_cast<void*>(il2cpp_utils::createcsstr(right))};
    Il2CppException* exp;
    Il2CppString* concatted = (Il2CppString*)il2cpp_functions::runtime_invoke(concat, nullptr, args, &exp);
    if (exp) {
        // ERROR VIA EXCEPTION
        log(ERROR, "%s", il2cpp_utils::ExceptionToString(exp).c_str());
        return nullptr;
    }
    log(DEBUG, "String concat with left: %s right: %s final: %s", to_utf8(csstrtostr(left)).c_str(), right.data(), to_utf8(csstrtostr(concatted)).c_str());
    return concatted;
}

static Il2CppString* concatBuffer(Il2CppString* left, Il2CppString* right) {
    void* args[] = {reinterpret_cast<void*>(left), reinterpret_cast<void*>(right)};
    Il2CppException* exp;
    Il2CppString* concatted = (Il2CppString*)il2cpp_functions::runtime_invoke(concat, nullptr, args, &exp);
    if (exp) {
        // ERROR VIA EXCEPTION
        log(ERROR, "%s", il2cpp_utils::ExceptionToString(exp).c_str());
        return nullptr;
    }
    log(DEBUG, "String concat with left: %s right: %s final: %s", to_utf8(csstrtostr(left)).c_str(), to_utf8(csstrtostr(right)).c_str(), to_utf8(csstrtostr(concatted)).c_str());
    return concatted;
}

static void checkJudgements(FlyingScoreEffect* scorePointer, int beforeCut, int afterCut, int cutDistance) {
    // log(DEBUG, "Getting required il2cpp classes/method infos...");
    static auto tmp_class = il2cpp_utils::GetClassFromName("TMPro", "TMP_Text");
    // log(DEBUG, "Initializing il2cpp_functions...");
    il2cpp_functions::Init();
    // log(DEBUG, "Using il2cpp_functions...");
    static auto set_richText = il2cpp_utils::GetMethod(tmp_class, "set_richText", 1);
    static auto set_enableWordWrapping = il2cpp_utils::GetMethod(tmp_class, "set_enableWordWrapping", 1);
    static auto set_overflowMode = il2cpp_utils::GetMethod(tmp_class, "set_overflowMode", 1);
    static auto get_text = il2cpp_utils::GetMethod(tmp_class, "get_text", 0);
    static auto set_text = il2cpp_utils::GetMethod(tmp_class, "set_text", 1);
    static auto str_class = il2cpp_utils::GetClassFromName("System", "String");
    // TODO MAKE THESE NOT USE PARAM COUNT
    // log(DEBUG, "Getting important string methods...");
    // log(DEBUG, "String Class Name: %s", il2cpp_functions::class_get_name(str_class));
    // TODO FIX YUCKY HACK
    // log(DEBUG, "Getting Method 98 for String.Replace");
    if (replace == nullptr) {
        log(INFO, "Getting string replace and concat methods!");
        replace = str_class->methods[97];
        concat = str_class->methods[113];
        log(INFO, "Got string methods!");
    }

    int score = beforeCut + afterCut + cutDistance;
    if (config.judgements.size() == 0) {
        log(WARNING, "Config not yet loaded (although it should be!) Loading now...");
        log(DEBUG, "Judgements Size: %lu", config.judgements.size());
        log(DEBUG, "BeforeCut Size: %lu", config.beforeCutAngleJudgements.size());
        log(DEBUG, "Accuracy Size: %lu", config.accuracyJudgements.size());
        log(DEBUG, "AfterCut Size: %lu", config.afterCutAngleJudgements.size());
        if (loadall()) {
            log(DEBUG, "Loaded Config!");
        } else {
            log(CRITICAL, "WILL CRASH, FAILED TO LOAD CONFIG A SECOND TIME!");
            exit(1);
        }
    }
    judgement best = config.judgements[config.judgements.size() - 1];
    for (int i = config.judgements.size()-2; i >= 0; i--) {
        if (config.judgements[i].threshold > score) {
            break;
        }
        best = config.judgements[i];
    }
    // log(DEBUG, "Setting score effect's color to best color with threshold: %d for score: %d", best.threshold, score);
    // TODO Add fading
    scorePointer->_color.r = best.r;
    scorePointer->_color.g = best.g;
    scorePointer->_color.b = best.b;
    scorePointer->_color.a = best.a;

    // Runtime invoke set_richText to true
    bool set_to = true;
    il2cpp_utils::RunMethod(scorePointer->_text, set_richText, &set_to);

    // Runtime invoke set_enableWordWrapping false
    set_to = false;
    il2cpp_utils::RunMethod(scorePointer->_text, set_enableWordWrapping, &set_to);

    // Runtime invoke set_overflowMode false
    il2cpp_utils::RunMethod(scorePointer->_text, set_overflowMode, &set_to);

    // Get Text
    Il2CppString* old_text;
    il2cpp_utils::RunMethod(&old_text, scorePointer->_text, get_text);

    Il2CppString* judgement_cs = il2cpp_utils::createcsstr(best.text);

    if (config.displayMode == DISPLAY_MODE_FORMAT) {
        // THIS IS VERY INEFFICIENT AND SLOW BUT SHOULD WORK!
        // log(DEBUG, "Displaying formated text!");
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
        log(DEBUG, "Displaying numeric text ONLY!");
        judgement_cs = old_text;
    } else if (config.displayMode == DISPLAY_MODE_SCOREONTOP) {
        // Score on top
        log(DEBUG, "Displaying score on top!");
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
    il2cpp_utils::RunMethod(scorePointer->_text, set_text, judgement_cs);
}

MAKE_HOOK_OFFSETLESS(rawScoreWithoutMultiplier, void, void* noteCutInfo, int* beforeCut, int* afterCut, int* cutDistance) {
    rawScoreWithoutMultiplier(noteCutInfo, beforeCut, afterCut, cutDistance);
}

MAKE_HOOK_OFFSETLESS(HandleSaberSwingRatingCounterDidChangeEvent, void, FlyingScoreEffect* self, void* saberSwingRatingCounter, float rating) {
    HandleSaberSwingRatingCounterDidChangeEvent(self, saberSwingRatingCounter, rating);
    
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    rawScoreWithoutMultiplier(self->_noteCutInfo, &beforeCut, &afterCut, &cutDistance);
    
    int score = beforeCut + afterCut;
    checkJudgements(self, beforeCut, afterCut, cutDistance);
}

void __attribute__((constructor)) lib_main()
{
    // Load config on construction
    log(INFO, "Loading configuration...");
    loadall();
}

extern "C" void load() {
    log(INFO, "Installing...");
    INSTALL_HOOK_OFFSETLESS(HandleSaberSwingRatingCounterDidChangeEvent, il2cpp_utils::GetMethod("", "FlyingScoreEffect", "HandleSaberSwingRatingCounterDidChangeEvent", 2));
    INSTALL_HOOK_OFFSETLESS(rawScoreWithoutMultiplier, il2cpp_utils::GetMethod("", "ScoreController", "RawScoreWithoutMultiplier", 4));
    log(INFO, "Installed!");
}

// CHECK_MOD_ANY;