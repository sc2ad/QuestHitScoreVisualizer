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

#define LOG_LEVEL CRITICAL | ERROR | WARNING | INFO | DEBUG

#include "../beatsaber-hook/shared/utils/utils.h"

#define RawScoreWithoutMultiplier_offset 0xA0AF4C
#define GetBeatmapDataFromBeatmapSaveData_offset 0x9BE268

MAKE_HOOK(rawScoreWithoutMultiplier, RawScoreWithoutMultiplier_offset, void, void* noteCutInfo, void* saberAfterCutSwingRatingCounter, int* beforeCut, int* afterCut, int* cutDistance) {
    log(DEBUG, "Called RawScoreWithoutMultiplier!");
    log(DEBUG, "Calling orig...");
    rawScoreWithoutMultiplier(noteCutInfo, saberAfterCutSwingRatingCounter, beforeCut, afterCut, cutDistance);
    log(DEBUG, "Score: %i", *beforeCut + *afterCut);
    log(DEBUG, "SUCCESS!");
}


Il2CppObject* textMeshObj;
#include "../beatsaber-hook/shared/utils/customui.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_GameObject.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_Object.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_Transform.h"
#include "../beatsaber-hook/shared/dumps/System_Type.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_Canvas.h"
#include "../beatsaber-hook/shared/dumps/UnityEngine_RectTransform.h"
#include "../beatsaber-hook/shared/dumps/TMPro_TMP_Text.h"

MAKE_HOOK(GetBeatmapDataFromBeatmapSaveData, GetBeatmapDataFromBeatmapSaveData_offset, void*, void* notesSaveData, void* obstaclesSaveData, void* eventsSaveData, float beatsPerMinute, float shuffle, float shufflePeriod) {
    log(DEBUG, "Entering BeatmapDataSO_get_beatmapData Hook!");
    if (!il2cpp_functions::initialized) {
        il2cpp_functions::Init();
    }
    log(DEBUG, "Attempting to call orig...");
    void* temp = GetBeatmapDataFromBeatmapSaveData(notesSaveData, obstaclesSaveData, eventsSaveData, beatsPerMinute, shuffle, shufflePeriod);;
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
    log(DEBUG, "Installing Simple Mod...");

    // il2cpp_functions::Init();
    // auto k = il2cpp_utils::GetClassFromName("", "ScoreController");
    // auto method = il2cpp_functions::class_get_method_from_name(k, "RawScoreWithoutMultiplier", 5);

    INSTALL_HOOK(rawScoreWithoutMultiplier);
    log(DEBUG, "Installed RawScoreWithoutMultiplier Hook!");
    INSTALL_HOOK(GetBeatmapDataFromBeatmapSaveData);
    log(DEBUG, "Installed GetBeatmapDataFromBeatmapSaveData Hook!");
}