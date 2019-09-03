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

#define MOD_ID "HitScoreVisualizer"
#define VERSION "1.9.3"

#define LOG_LEVEL CRITICAL | ERROR | WARNING | INFO | DEBUG

#include "../beatsaber-hook/shared/utils/utils.h"
#include "../beatsaber-hook/shared/utils/customui.h"
#include "../beatsaber-hook/rapidjson/include/rapidjson/document.h"
#include "../beatsaber-hook/rapidjson/include/rapidjson/allocators.h"
#include "main.h"

#define HandleSaberAfterCutSwingRatingCounterDidChangeEvent_offset 0xA4D338
#define GetBeatmapDataFromBeatmapSaveData_offset 0x9A1D0C
#define RawScoreWithoutMultiplier_offset 0xA0DA14

static auto& config_doc = Configuration::config;
static struct Config config;
static bool loadedConfig = false;

// static void addJudgement(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &alloc, rapidjson::GenericArray<false, ConfigValue> arr, int thresh, std::string_view text, std::vector<float> colors, bool fade = false) {
//     auto v = ConfigValue(rapidjson::kObjectType).GetObject();
//     v.AddMember(ConfigValue("threshold"), ConfigValue(thresh), alloc);
//     v.AddMember("threshold", ConfigValue(thresh), alloc);
//     v.AddMember("text", ConfigValue(text.data(), text.length()), alloc);
//     auto color = ConfigValue(rapidjson::kArrayType).GetArray();
//     for (int i = 0; i < 4; i++) {
//         color.PushBack(ConfigValue(colors[i]), alloc);
//     }
//     v.AddMember("color", color, alloc);
//     v.AddMember("fade", rapidjson::Value(fade), alloc);
//     arr.PushBack(v, alloc);
// }

// static void addSegment(rapidjson::MemoryPoolAllocator<> &alloc, rapidjson::GenericArray<false, rapidjson::Value> arr, int thresh, std::string_view text) {
//     auto v = rapidjson::Value(rapidjson::kObjectType);
//     v.AddMember("threshold", rapidjson::Value(thresh), alloc);
//     v.AddMember("text", rapidjson::Value(text.data(), text.length()), alloc);
//     arr.PushBack(v, alloc);
// }

static void createdefaultjson() {
    // log(DEBUG, "Attempting to create default config");
    // rapidjson::Document& doc = Configuration::Load();
    // rapidjson::MemoryPoolAllocator<> &alloc = doc.GetAllocator();
    // doc.RemoveAllMembers();
    // doc.AddMember("majorVersion", rapidjson::Value(2), alloc);
    // doc.AddMember("minorVersion", rapidjson::Value(2), alloc);
    // doc.AddMember("patchVersion", rapidjson::Value(0), alloc);
    // auto judgements = rapidjson::Value(rapidjson::kArrayType).GetArray();
    // addJudgement(alloc, judgements, 115, "%BFantastic%A%n%s", {1.0, 1.0, 1.0, 1.0});
    // addJudgement(alloc, judgements, 101, "<size=80%>%BExcellent%A</size>%n%s", {0.0, 1.0, 0.0, 1.0});
    // addJudgement(alloc, judgements, 90, "<size=80%>%BGreat%A</size>%n%s", {1.0, 0.980392158, 0.0, 1.0});
    // addJudgement(alloc, judgements, 80, "<size=80%>%BGood%A</size>%n%s", {1.0, 0.6, 0.0, 1.0}, true);
    // addJudgement(alloc, judgements, 60, "<size=80%>%BDecent%A</size>%n%s", {1.0, 0.0, 0.0, 1.0}, true);
    // addJudgement(alloc, judgements, 0, "<size=80%>%BWay Off%A</size>%n%s", {0.5, 0.0, 0.0, 1.0}, true);
    // doc.AddMember("judgements", judgements, alloc);
    // auto beforeCutAngleJudgements = rapidjson::Value(rapidjson::kArrayType).GetArray();
    // addSegment(alloc, beforeCutAngleJudgements, 70, "+");
    // addSegment(alloc, beforeCutAngleJudgements, 0, " ");
    // doc.AddMember("beforeCutAngleJudgements", beforeCutAngleJudgements, alloc);
    // auto accuracyJudgements = rapidjson::Value(rapidjson::kArrayType).GetArray();
    // addSegment(alloc, accuracyJudgements, 15, "+");
    // addSegment(alloc, accuracyJudgements, 0, " ");
    // doc.AddMember("accuracyJudgements", accuracyJudgements, alloc);
    // auto afterCutAngleJudgements = rapidjson::Value(rapidjson::kArrayType).GetArray();
    // addSegment(alloc, afterCutAngleJudgements, 30, "+");
    // addSegment(alloc, afterCutAngleJudgements, 0, " ");
    // doc.AddMember("afterCutAngleJudgements", afterCutAngleJudgements, alloc);
    // doc.AddMember("useJson", rapidjson::Value(true), alloc);
    // log(DEBUG, "Attempting to write config");
    // Configuration::Write();

    // log(INFO, "Created default JSON config!");

    const char* js = "\n{\n"
    "\t\"majorVersion\": 2,\n"
    "\t\"minorVersion\": 2,\n"
    "\t\"displayMode\": \"format\",\n"
    "\t\"judgments\":[\n"
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
    "\t],\n"
    "\t\"useJson\": true\n"
    "}";

    std::string filename = getconfigpath();

    int r = writefile(filename.c_str(), js);
    if (r == 0) {
        log(INFO, "CREATED DEFAULT JSON FILE AT PATH: %s", filename.c_str());
    }
    else if (r == WRITE_ERROR_COULD_NOT_MAKE_FILE) {
        log(INFO, "COULD NOT MAKE DEFAULT JSON FILE AT PATH: %s", filename.c_str());
    }
}

static void createdefault() {
    config.judgements.reserve(6);
    // Creating Fantastic judgement
    config.judgements.assign(6, {115, 1.0f, 1.0f, 1.0f, 1.0f, "Moon Struck!", false});
    // Creating Excellent judgement
    config.judgements[1] = {101, 0.0f, 1.0f, 0.0f, 1.0f, "<size=80%>Sugar Crush!</size>", true};
    // Creating Great judgement
    config.judgements[2] = {90, 1.0f, 0.980392158f, 0.0f, 1.0f, "<size=80%>Divine</size>", true};
    // Creating Good judgement
    config.judgements[3] = {80, 1.0f, 0.6f, 0.0f, 1.0f, "<size=80%>Delicious</size>", true};
    // Creating Decent judgement
    config.judgements[4] = {60, 1.0f, 0.0f, 0.0f, 1.0f, "<size=80%>Tasty</size>", true};
    // Creating Way Off judgement
    config.judgements[5] = {0, 0.5f, 0.0f, 0.0f, 1.0f, "<size=80%>Sweet</size>", true};
    // Set displaymode
    config.displayMode = DISPLAY_MODE_TEXTONTOP;
    // Set BeforeCutSegments
    config.beforeCutAngleJudgements.reserve(6);
    config.beforeCutAngleJudgements.assign(2, {70, "+"});
    config.beforeCutAngleJudgements[1] = {0, " "};
    // Set AccuracySegments
    config.accuracyJudgements.reserve(6);
    config.accuracyJudgements.assign(2, {15, "+"});
    config.accuracyJudgements[1] = {0, " "};
    // Set AfterCut
    config.afterCutAngleJudgements.reserve(6);
    config.afterCutAngleJudgements.assign(2, {30, "+"});
    config.afterCutAngleJudgements[1] = {0, " "};

    log(DEBUG, "Created default judgements!");
    log(DEBUG, "Judgements Size: %lu", config.judgements.size());
    log(DEBUG, "BeforeCut Size: %lu", config.beforeCutAngleJudgements.size());
    log(DEBUG, "Accuracy Size: %lu", config.accuracyJudgements.size());
    log(DEBUG, "AfterCut Size: %lu", config.afterCutAngleJudgements.size());
}

static bool createjudgements(rapidjson::GenericArray<false, ConfigValue> arr) {
    int index = 0;
    // config.judgements.clear();
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
    // rapidjson::Document& config_doc = Configuration::Load();

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
            if (!createjudgements(itr->value.GetArray())) {
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

static void loadall() {
    log(INFO, "Loading Configuration...");
    Configuration::Load();
    log(INFO, "Loaded Configuration!");
    log(DEBUG, "Created Initial Config Object, should no longer be null!");
    int r = loadjudgements();
    if (r == -2) {
        createdefaultjson();
        log(INFO, "Loading default JSON...");
        r = loadjudgements();
    } if (r == -1) {
        log(INFO, "Loading candy crush config");
        createdefault();
    } if (r == -2) {
        log(CRITICAL, "COULD NOT LOAD DEFAULT JSON!");
        createdefault();
    }
    if (r == 0) {
        log(INFO, "Successfully loaded judgements from JSON!");
    }
    log(DEBUG, "Sizes: %lu, %lu, %lu, %lu", config.judgements.size(), config.beforeCutAngleJudgements.size(), config.accuracyJudgements.size(), config.afterCutAngleJudgements.size());
    loadedConfig = true;
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

static bool __cached = false;
static Il2CppClass* tmp_class;
static const MethodInfo* set_richText;
static const MethodInfo* set_enableWordWrapping;
static const MethodInfo* set_overflowMode;
static const MethodInfo* get_text;
static const MethodInfo* set_text;
static Il2CppClass* str_class;
static const MethodInfo* concat;
static const MethodInfo* replace;

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
    Il2CppString* concatted = (Il2CppString*)il2cpp_functions::runtime_invoke(replace, nullptr, args, &exp);
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
    Il2CppString* concatted = (Il2CppString*)il2cpp_functions::runtime_invoke(replace, nullptr, args, &exp);
    if (exp) {
        // ERROR VIA EXCEPTION
        log(ERROR, "%s", il2cpp_utils::ExceptionToString(exp).c_str());
        return nullptr;
    }
    return concatted;
}

static void checkJudgements(FlyingScoreEffect* scorePointer, int beforeCut, int afterCut, int cutDistance) {
    if (!__cached) {
        log(DEBUG, "Getting required il2cpp classes/method infos...");
        tmp_class = il2cpp_utils::GetClassFromName("TMPro", "TMP_Text");
        log(DEBUG, "Initializing il2cpp_functions...");
        il2cpp_functions::Init();
        log(DEBUG, "Using il2cpp_functions...");
        set_richText = il2cpp_functions::class_get_method_from_name(tmp_class, "set_richText", 1);
        set_enableWordWrapping = il2cpp_functions::class_get_method_from_name(tmp_class, "set_enableWordWrapping", 1);
        set_overflowMode = il2cpp_functions::class_get_method_from_name(tmp_class, "set_overflowMode", 1);
        get_text = il2cpp_functions::class_get_method_from_name(tmp_class, "get_text", 0);
        set_text = il2cpp_functions::class_get_method_from_name(tmp_class, "set_text", 1);
        str_class = il2cpp_utils::GetClassFromName("System", "String");
        // TODO MAKE THESE NOT USE PARAM COUNT
        log(DEBUG, "Getting important string methods...");
        log(DEBUG, "String Class Name: %s", il2cpp_functions::class_get_name(str_class));
        // TODO FIX YUCKY HACK
        log(DEBUG, "Getting Method 98 for String.Replace");
        replace = str_class->methods[97];
        log(DEBUG, "Getting Method 114 for String.Concat");
        concat = str_class->methods[113];
        // il2cpp_utils::LogClass(str_class, false);
        // const MethodInfo* current;
        // void* myIter;
        // while ((current = il2cpp_functions::class_get_methods(str_class, &myIter))) {
        //     if (current->parameters_count != 2) {
        //         continue;
        //     }
        //     log(DEBUG, "Found method with 2 parameters");
        //     log(DEBUG, "Method Name: %s", current->name);
        //     for (int i = 0; i < current->parameters_count; i++) {
        //         log(DEBUG, "Parameter: %lu: %s", i, il2cpp_functions::type_get_name(current->parameters[i].parameter_type));
        //         if (!il2cpp_functions::type_equals(current->parameters[i].parameter_type, il2cpp_functions::class_get_type_const(str_class))) {
        //             goto next_method;
        //         }
        //     }
        //     if (strcmp(current->name, "Concat") == 0) {
        //         log(DEBUG, "Found String.Concat(string, string)");
        //         concat = current;
        //     } else if (strcmp(current->name, "Replace") == 0) {
        //         log(DEBUG, "Found String.Replace(string, string)");
        //         replace = current;
        //     }
        //     next_method:;
        // }
    }

    int score = beforeCut + afterCut;
    if (loadedConfig) {
        log(DEBUG, "Loaded Config!");
    }
    if (!loadedConfig || config.judgements.size() == 0) {
        log(DEBUG, "Config not yet loaded! Loading now...");
        log(DEBUG, "Judgements Size: %lu", config.judgements.size());
        log(DEBUG, "BeforeCut Size: %lu", config.beforeCutAngleJudgements.size());
        log(DEBUG, "Accuracy Size: %lu", config.accuracyJudgements.size());
        log(DEBUG, "AfterCut Size: %lu", config.afterCutAngleJudgements.size());
        loadall();
        if (loadedConfig) {
            log(DEBUG, "Loaded Config!");
        }
    }
    log(DEBUG, "Checking judgements for score: %d", score);
    log(DEBUG, "Config Judgements Size: %lu", config.judgements.size());
    log(DEBUG, "0th Item Text: %s", config.judgements[0].text);
    judgement best = config.judgements[config.judgements.size() - 1];
    for (int i = config.judgements.size()-2; i >= 0; i--) {
        if (config.judgements[i].threshold > score) {
            break;
        }
        best = config.judgements[i];
    }
    log(DEBUG, "Setting score effect's color to best color with threshold: %d for score: %d", best.threshold, score);
    // TODO Add fading
    scorePointer->_color.r = best.r;
    scorePointer->_color.g = best.g;
    scorePointer->_color.b = best.b;
    scorePointer->_color.a = best.a;
    log(DEBUG, "Modified color!");

    // Runtime invoke set_richText to true
    bool set_to = true;
    if (!il2cpp_utils::RunMethod(scorePointer->_text, set_richText, &set_to)) {
        // ERROR VIA EXCEPTION
        return;
    }

    // Runtime invoke set_enableWordWrapping false
    set_to = false;
    if (!il2cpp_utils::RunMethod(scorePointer->_text, set_enableWordWrapping, &set_to)) {
        // ERROR VIA EXCEPTION
        return;
    }

    // Runtime invoke set_overflowMode false
    if (!il2cpp_utils::RunMethod(scorePointer->_text, set_overflowMode, &set_to)) {
        // ERROR VIA EXCEPTION
        return;
    }

    // Get Text
    Il2CppException* exp;
    Il2CppString* old_text = (Il2CppString*)il2cpp_functions::runtime_invoke(get_text, scorePointer->_text, nullptr, &exp);
    if (exp) {
        // ERROR VIA EXCEPTION
        log(ERROR, "%s", il2cpp_utils::ExceptionToString(exp).c_str());
        return;
    }

    Il2CppString* judgement_cs = il2cpp_utils::createcsstr(best.text);

    if (config.displayMode == DISPLAY_MODE_FORMAT) {
        // THIS IS VERY INEFFICIENT AND SLOW BUT SHOULD WORK!
        log(DEBUG, "Displaying formated text!");
        char buffer[4]; // Max length for score buffers is 3
        // %b
        sprintf(buffer, "%d", beforeCut);
        judgement_cs = replaceBuffer(judgement_cs, "%b", buffer);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %c
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%d", cutDistance);
        judgement_cs = replaceBuffer(judgement_cs, "%c", buffer);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %a
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%d", afterCut);
        judgement_cs = replaceBuffer(judgement_cs, "%a", buffer);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %B
        const char* bestBeforeSeg = getBestSegment(config.beforeCutAngleJudgements, beforeCut);
        judgement_cs = replaceBuffer(judgement_cs, "%B", bestBeforeSeg);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %C
        const char* bestCutAcc = getBestSegment(config.accuracyJudgements, cutDistance);
        judgement_cs = replaceBuffer(judgement_cs, "%C", bestCutAcc);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %A
        const char* bestAfterSeg = getBestSegment(config.afterCutAngleJudgements, afterCut);
        judgement_cs = replaceBuffer(judgement_cs, "%A", bestAfterSeg);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %s
        buffer[1] = '\0'; buffer[2] = '\0'; // Reset buffer
        sprintf(buffer, "%d", score);
        judgement_cs = replaceBuffer(judgement_cs, "%s", buffer);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %p
        char percentBuff[7]; // 6 is upper bound for 100.00 percent
        sprintf(percentBuff, "%.2f", score / 115.0 * 100.0);
        judgement_cs = replaceBuffer(judgement_cs, "%p", percentBuff);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %%
        judgement_cs = replaceBuffer(judgement_cs, "%%", "%");
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
        // %n
        judgement_cs = replaceBuffer(judgement_cs, "%n", "\n");
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
    }
    else if (config.displayMode == DISPLAY_MODE_NUMERIC) {
        // Numeric display ONLY
        log(DEBUG, "Displaying numeric text ONLY!");
        judgement_cs = old_text;
    }
    else if (config.displayMode == DISPLAY_MODE_SCOREONTOP) {
        // Score on top
        log(DEBUG, "Displaying score on top!");
        // Add newline
        judgement_cs = concatBuffer(concatBuffer(old_text, "\n"), best.text);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
    }
    else {
        // Text on top
        log(DEBUG, "Displaying judgement text on top!");
        log(DEBUG, "Old Text: %s", to_utf8(csstrtostr(old_text)).c_str());
        auto temp = concatBuffer(judgement_cs, "\n");
        log(DEBUG, "New temp text: %s", to_utf8(csstrtostr(temp)).c_str());
        // Add newline
        judgement_cs = concatBuffer(temp, old_text);
        if (!judgement_cs) {
            // ERROR VIA EXCEPTION
            return;
        }
    }

    if (!il2cpp_utils::RunMethod(scorePointer->_text, set_text, judgement_cs)) {
        // ERROR VIA EXCEPTION
        return;
    }
}

MAKE_HOOK(rawScoreWithoutMultiplier, RawScoreWithoutMultiplier_offset, void, void* noteCutInfo, int* beforeCut, int* afterCut, int* cutDistance) {
    log(DEBUG, "Called RawScoreWithoutMultiplier!");
    log(DEBUG, "Calling orig...");
    log(DEBUG, "Judgements Size: %lu", config.judgements.size());
    rawScoreWithoutMultiplier(noteCutInfo, beforeCut, afterCut, cutDistance);
    log(DEBUG, "SUCCESS!");
}

static void dump_real(int before, int after, void* ptr) {
    log(DEBUG, "Dumping Immediate Pointer: %p: %lx", ptr, *reinterpret_cast<long*>(ptr));
    auto begin = static_cast<long*>(ptr) - before;
    auto end = static_cast<long*>(ptr) + after;
    for (auto cur = begin; cur != end; ++cur) {
        log(DEBUG, "0x%lx: %lx", (long)cur - (long)ptr, *cur);
    }
}

MAKE_HOOK(HandleSaberAfterCutSwingRatingCounterDidChangeEvent, HandleSaberAfterCutSwingRatingCounterDidChangeEvent_offset, void, FlyingScoreEffect* self, void* saberSwingRatingCounter, float rating) {
    log(DEBUG, "Called HandleSaberAfterCutSwingRatingCounterDidChangeEvent Hook!");
    if (!il2cpp_functions::initialized) {
        il2cpp_functions::Init();
    }
    log(DEBUG, "Judgements.Size: %lu", config.judgements.size());
    log(DEBUG, "Attempting to call standard HandleSaberAfterCutSwingRatingCounterDidChangeEvent...");
    HandleSaberAfterCutSwingRatingCounterDidChangeEvent(self, saberSwingRatingCounter, rating);
    log(DEBUG, "Called orig!");
    if (loadedConfig) log(DEBUG, "Loaded Config!");
    
    int beforeCut = 0;
    int afterCut = 0;
    int cutDistance = 0;
    // int* ptr_beforeCut = &beforeCut;
    // int* ptr_afterCut = &afterCut;
    // int* ptr_cutDistance = &cutDistance;
    // log(DEBUG, "Creating boxed values...");
    // auto beforeCutBox = il2cpp_functions::value_box(IntClass, &beforeCut);
    // auto afterCutBox = il2cpp_functions::value_box(IntClass, &afterCut);
    // auto cutDistanceBox = il2cpp_functions::value_box(IntClass, &cutDistance);

    // il2cpp_utils::LogMethod(rawScoreWithoutMultiplier);

    log(DEBUG, "Attempting to call ScoreController.RawScoreWithoutMultiplier...");
    
    // void* args[] = {self->noteCutInfo, self->saberAfterCutSwingRatingCounter, &beforeCutBox, &afterCutBox, &cutDistanceBox};
    // Il2CppException* exp;
    // il2cpp_functions::runtime_invoke(rawScoreWithoutMultiplier, nullptr, args, &exp);
    // if (exp) {
    //     // ERROR FROM EXCEPTION
    //     log(ERROR, "%s", il2cpp_utils::ExceptionToString(exp).c_str());
    //     return;
    // }

    // log(DEBUG, "Dumping various info...");

    // log(DEBUG, "Dumping _moveAnimationCurve loc: %p", self->_moveAnimationCurve);
    // log(DEBUG, "Dumping _fadeAnimationCurve loc: %p", self->_fadeAnimationCurve);
    // log(DEBUG, "Dumping _noteCutInfo loc: %p", self->_noteCutInfo);

    // dump_real(0, 32, self);

    rawScoreWithoutMultiplier(self->_noteCutInfo, &beforeCut, &afterCut, &cutDistance);
    
    int score = beforeCut + afterCut;
    log(DEBUG, "RawScore: %d", score);
    log(DEBUG, "Checking judgements...");
    checkJudgements(self, beforeCut, afterCut, cutDistance);
    log(DEBUG, "Completed HandleSaberAfterCutSwingRatingCounterDidChangeEvent!");
}

Il2CppObject* textMeshObj;

#include "../beatsaber-hook/shared/dumps/UnityEngine_GameObject.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_Object.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_Transform.h"
#include "../beatsaber-hook/shared/dumps/System_Type.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_Canvas.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_RectTransform.h"
#include "../beatsaber-hook/shared/dumps/TMPro_TMP_Text.h"

MAKE_HOOK(GetBeatmapDataFromBeatmapSaveData, GetBeatmapDataFromBeatmapSaveData_offset, void*, void* one, void* two, void* three, float four, float five, float six) {
    log(DEBUG, "Entering BeatmapDataSO_get_beatmapData Hook!");
    if (!il2cpp_functions::initialized) {
        il2cpp_functions::Init();
    }
    log(DEBUG, "Attempting to call orig...");
    void* temp = GetBeatmapDataFromBeatmapSaveData(one, two, three, four, five, six);;
    log(DEBUG, "Attempting to create text!");

    log(DEBUG, "Initializing all il2cpp method infos");
    UnityEngine_GameObject::Init();
    UnityEngine_Object::Init();
    UnityEngine_Transform::Init();
    System_Type::Init();
    UnityEngine_Canvas::Init();
    UnityEngine_RectTransform::Init();
    TMPro_TMP_Text::Init();
    log(DEBUG, "Creating GameObject");
    // CRASHED HERE MOST RECENTLY: 8/14/2019
    auto go = il2cpp_utils::NewUnsafe(UnityEngine_GameObject::klass, il2cpp_utils::createcsstr("Custom Text Test"));
    log(DEBUG, "Created GameObject!");
    Il2CppException* exp;
    // void* args1[] = {go};
    // il2cpp_functions::runtime_invoke(UnityEngine_Object::DontDestroyOnLoad_Object, nullptr, args1, &exp);
    // log(DEBUG, "DontDestroyOnLoad GameObject!");
    auto transform = il2cpp_functions::runtime_invoke(UnityEngine_GameObject::get_transform, go, nullptr, &exp);
    log(DEBUG, "Got Transform");
    // Set position
    Vector3 pos = {0, 0, 2.5};
    void* args2[] = {&pos};
    il2cpp_functions::runtime_invoke(UnityEngine_Transform::set_position, transform, args2, &exp);
    log(DEBUG, "Set position");
    // Set euler angles
    Vector3 eulerAng = {0, 0, 0};
    void* args3[] = {&eulerAng};
    il2cpp_functions::runtime_invoke(UnityEngine_Transform::set_eulerAngles, transform, args3, &exp);
    log(DEBUG, "Set eulerAngles");
    // Set local scale
    Vector3 localScale = {0.01, 0.01, 0.01};
    void* args4[] = {&localScale};
    il2cpp_functions::runtime_invoke(UnityEngine_Transform::set_localScale, transform, args4, &exp);
    log(DEBUG, "Set localScale");
    // Get Canvas Type
    void* args5[] = {il2cpp_utils::createcsstr("UnityEngine.Canvas")};
    auto canvas_type = il2cpp_functions::runtime_invoke(System_Type::GetType_string, nullptr, args5, &exp);
    log(DEBUG, "Got Canvas Type");
    // Add Canvas Component
    void* args6[] = {canvas_type};
    auto canvas = il2cpp_functions::runtime_invoke(UnityEngine_GameObject::AddComponent_Type, go, args6, &exp);
    log(DEBUG, "Added Canvas Component");
    // Set Canvas Render Mode
    int world_render_mode = 2;
    void* args7[] = {&world_render_mode};
    il2cpp_functions::runtime_invoke(UnityEngine_Canvas::set_renderMode, canvas, args7, &exp);
    log(DEBUG, "Set RenderMode");
    // Set sizeDelta
    Vector2 sizeDelta = {200, 50};
    void* args8[] = {&sizeDelta};
    il2cpp_functions::runtime_invoke(UnityEngine_RectTransform::set_sizeDelta, canvas, args8, &exp);
    log(DEBUG, "Set sizeDelta");
    // Create custom UI text
    textMeshObj = CustomUI::createtext(go, "This is my own custom text!", {0, -30}, {400, 20});
    log(DEBUG, "Created Custom Text");
    // Set fontSize
    float placeholder = 10;
    void* args9[] = {&placeholder};
    il2cpp_functions::runtime_invoke(TMPro_TMP_Text::set_fontSize, textMeshObj, args9, &exp);
    log(DEBUG, "Set fontSize");
    // Set Alignment
    int textAlignment_center = 1;
    // void* args10[] = {&textAlignment_center};
    // il2cpp_functions::runtime_invoke(TMPro_TMP_Text::set_alignment, textMeshObj, args10, &exp);
    // il2cpp_functions::runtime_invoke(TMPro_TMP_Text::set_alignment, textMeshObj, {reinterpret_cast<void*>(&textAlignment_center)}, &exp);
    il2cpp_utils::RuntimeInvoke(TMPro_TMP_Text::set_alignment, textMeshObj, &exp, &textAlignment_center);
    log(DEBUG, "Set alignment");
    log(DEBUG, "COMPLETE!");
    return temp;
}

__attribute__((constructor)) void lib_main()
{
    #ifdef __aarch64__
    log(INFO, "Is 64 bit!");
    #endif
    log(DEBUG, "Installing HitScoreVisualizer...");
    // INSTALL_HOOK(init_and_present);
    // log("Installed InitAndPresent Hook!");
    INSTALL_HOOK(HandleSaberAfterCutSwingRatingCounterDidChangeEvent);
    log(DEBUG, "Installed HandleSaberAfterCutSwingRatingCounterDidChangeEvent Hook!");
    INSTALL_HOOK(rawScoreWithoutMultiplier);
    log(DEBUG, "Installed RawScoreWithoutMultiplier Hook!");
    // INSTALL_HOOK(GetBeatmapDataFromBeatmapSaveData);
    // log(DEBUG, "Installed BeatmapDataLoader.GetBeatmapDataFromBeatmapSaveData Hook!");
    // Attempt to add and create judgements
    // Attempt to find judgements
    log(DEBUG, "Created Config Wrapper!");
    loadall();
}