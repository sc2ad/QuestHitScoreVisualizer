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
#define VERSION "1.9.0"

#define LOG_LEVEL CRITICAL | ERROR | WARNING | INFO | DEBUG

#include "../beatsaber-hook/shared/utils/utils.h"
#include "../beatsaber-hook/rapidjson/include/rapidjson/document.h"
#include "../beatsaber-hook/rapidjson/include/rapidjson/allocators.h"
#include "main.h"

Config config;

void createdefaultjson(const char* filename) {
    const char* js = "\n{\n"
    "\t\"majorVersion\": 2,\n"
    "\t\"minorVersion\": 2,\n"
    "\t\"displayMode\": \"format\",\n"
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
    "\t],\n"
    "\t\"useJson\": true\n"
    "}";
    int r = writefile(filename, js);
    if (r == 0) {
        log(INFO, "CREATED DEFAULT JSON FILE AT PATH: %s", filename);
    }
    else if (r == WRITE_ERROR_COULD_NOT_MAKE_FILE) {
        log(INFO, "COULD NOT MAKE DEFAULT JSON FILE AT PATH: %s", filename);
    }
}

void createdefault() {
    config.judgements.reserve(6);
    // Creating Fantastic judgement
    config.judgements[0] = {115, 1.0f, 1.0f, 1.0f, 1.0f, "Moon Struck!", false};
    // Creating Excellent judgement
    judgement excellent = 
    config.judgements[1] = {101, 0.0f, 1.0f, 0.0f, 1.0f, "<size=80%>Sugar Crush!</size>", true};
    // Creating Great judgement
    judgement great = {90, 1.0f, 0.980392158f, 0.0f, 1.0f, "<size=80%>Divine</size>", '\1'};
    config.judgements[2] = great;
    // Creating Good judgement
    judgement good = {80, 1.0f, 0.6f, 0.0f, 1.0f, "<size=80%>Delicious</size>", '\1'};
    config.judgements[3] = good;
    // Creating Decent judgement
    judgement decent = {60, 1.0f, 0.0f, 0.0f, 1.0f, "<size=80%>Tasty</size>", '\1'};
    config.judgements[4] = decent;
    // Creating Way Off judgement
    judgement way_off = {0, 0.5f, 0.0f, 0.0f, 1.0f, "<size=80%>Sweet</size>", '\1'};
    config.judgements[5] = way_off;
    // Set displaymode
    config.displayMode = DISPLAY_MODE_TEXTONTOP;
    // Set BeforeCutSegments
    config.beforeCutAngleJudgements.reserve(2);
    config.beforeCutAngleJudgements[0] = {70, "+"};
    config.beforeCutAngleJudgements[1] = {0, " "};
    // Set AccuracySegments
    config.accuracyJudgements.reserve(2);
    config.accuracyJudgements[0] = {15, "+"};
    config.accuracyJudgements[1] = {0, " "};
    // Set AfterCut
    config.afterCutAngleJudgements.reserve(2);
    config.afterCutAngleJudgements[0] = {30, "+"};
    config.afterCutAngleJudgements[1] = {0, " "};

    log(DEBUG, "Created default judgements!");
}

bool createjudgements(rapidjson::GenericArray<false, rapidjson::Value> arr) {
    int index = 0;
    config.judgements.reserve(arr.Capacity());
    for (auto& v : arr) {
        if (!v.IsObject()) {
            // ERROR
            return false;
        }
        for (auto jitr = v.GetObject().MemberBegin(); jitr != v.GetObject().MemberEnd(); jitr++) {
            if (strcmp(jitr->name.GetString(), "threshold") == 0) {
                if (!jitr->value.IsInt()) {
                    // ERROR
                    return false;
                }
                config.judgements[index].threshold = jitr->value.GetInt();
            }
            else if (strcmp(jitr->name.GetString(), "text") == 0) {
                if (!jitr->value.IsString()) {
                    // ERROR
                    return false;
                }
                config.judgements[index].text = jitr->value.GetString();
            }
            else if (strcmp(jitr->name.GetString(), "color") == 0) {
                if (!jitr->value.IsArray()) {
                    // ERROR
                    return false;
                }
                int ci = 0;
                for (auto& c : jitr->value.GetArray()) {
                    if (!c.IsFloat()) {
                        // ERROR
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
                    return false;
                }
                config.judgements[index].fade = jitr->value.GetBool();
            }
        }
        index++;
    }
    return true;
}

bool createjudgementsegments(std::vector<judgement_segment> vec, rapidjson::GenericArray<false, rapidjson::Value> arr) {
    int index = 0;
    vec.reserve(arr.Capacity());
    for (auto& v : arr) {
        if (!v.IsObject()) {
            // ERROR
            return false;
        }
        for (auto jitr = v.GetObject().MemberBegin(); jitr != v.GetObject().MemberEnd(); jitr++) {
            if (strcmp(jitr->name.GetString(), "threshold") == 0) {
                if (!jitr->value.IsInt()) {
                    // ERROR
                    return false;
                }
                vec[index].threshold = jitr->value.GetInt();
            }
            else if (strcmp(jitr->name.GetString(), "text") == 0) {
                if (!jitr->value.IsString()) {
                    // ERROR
                    return false;
                }
                vec[index].text = jitr->value.GetString();
            }
        }
        index++;
    }
    return true;
}

int loadjudgements() {
    auto json_doc = Configuration::Load();

    // Two approach ideas:
    // 1. Iterate over all members
    // 2. Call FindMember a bunch of times
    // 1:
    if (json_doc.HasMember("useJson")) {
        if (!json_doc["useJson"].IsBool()) {
            json_doc["useJson"].SetBool(true);
            Configuration::Write();
        }
        if (!json_doc["useJson"].GetBool()) {
            // Exit without parsing the JSON
            return -1;
        }
    }
    for (auto itr = json_doc.MemberBegin(); itr != json_doc.MemberEnd(); itr++) {
        if (strcmp(itr->name.GetString(), "majorVersion") == 0) {
            if (!itr->value.IsInt()) {
                // ERROR
            }
            config.majorVersion = itr->value.GetInt();
        }
        else if (strcmp(itr->name.GetString(), "minorVersion") == 0) {
            if (!itr->value.IsInt()) {
                // ERROR
            }
            config.minorVersion = itr->value.GetInt();
        }
        else if (strcmp(itr->name.GetString(), "patchVersion") == 0) {
            if (!itr->value.IsInt()) {
                // ERROR
            }
            config.patchVersion = itr->value.GetInt();
        }
        else if (strcmp(itr->name.GetString(), "displayMode") == 0) {
            if (!itr->value.IsString()) {
                // ERROR
            }
            if (strcmp(itr->value.GetString(), "format")) {
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
        }
        else if (strcmp(itr->name.GetString(), "judgements") == 0) {
            if (!itr->value.IsArray()) {
                // ERROR
            }
            if (!createjudgements(itr->value.GetArray())) {
                // ERROR
            }
        }
        else if (strcmp(itr->name.GetString(), "beforeCutAngleJudgements") == 0) {
            if (!itr->value.IsArray()) {
                // ERROR
            }
            if (!createjudgementsegments(config.beforeCutAngleJudgements, itr->value.GetArray())) {
                // ERROR
            }
        }
        else if (strcmp(itr->name.GetString(), "accuracyJudgements") == 0) {
            if (!itr->value.IsArray()) {
                // ERROR
            }
            if (!createjudgementsegments(config.accuracyJudgements, itr->value.GetArray())) {
                // ERROR
            }
        }
        else if (strcmp(itr->name.GetString(), "afterCutAngleJudgements") == 0) {
            if (!itr->value.IsArray()) {
                // ERROR
            }
            if (!createjudgementsegments(config.afterCutAngleJudgements, itr->value.GetArray())) {
                // ERROR
            }
        }
    }
    if (config.majorVersion < 2 || (config.majorVersion == 2 && config.minorVersion < 2) || (config.majorVersion == 2 && config.minorVersion == 2 && config.patchVersion < 0)) {
        // VERSION ERROR
        return -1;
    }
    return 0;
}

