#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#include "../beatsaber-hook/shared/inline-hook/inlineHook.h"
#include "../beatsaber-hook/shared/utils/utils.h"

#undef log
#define log(...) __android_log_print(ANDROID_LOG_INFO, "QuestHook", "[Most-Bestest-Song] " __VA_ARGS__)

// GameObject gameObj = new GameObject("CustomUIText");
// gameObj.SetActive(false);

// TextMeshProUGUI textMesh = gameObj.AddComponent<TextMeshProUGUI>();
// What happens if we don't use font? Try and see.
// textMesh.font = Instantiate(Resources.FindObjectsOfTypeAll<TMP_FontAsset>().First(t => t.name == "Teko-Medium SDF No Glow"));
// textMesh.rectTransform.SetParent(parent, false);
// textMesh.text = text;
// textMesh.fontSize = 4;
// textMesh.color = Color.white;

// All of these are properties that we need to do set operations on.
// textMesh.rectTransform.anchorMin = new Vector2(0.5f, 0.5f);
// textMesh.rectTransform.anchorMax = new Vector2(0.5f, 0.5f);
// textMesh.rectTransform.sizeDelta = sizeDelta;
// textMesh.rectTransform.anchoredPosition = anchoredPosition;

// gameObj.SetActive(true);
// return textMesh;

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color;

void* createText(void* rectTransformParent, char text[], Vector2 anchoredPosition, Vector2 sizeDelta) {
    log("Creating text: %s", text);
    log("Attempting to create new gameobject...");
    // GameObject.ctor(string name): 0xC7643C
    void* gameobj = malloc(sizeof(GameObject)); // YIKES!
    log("Attempting to disable the active state of the gameobject...");
    // GameObject.SetActive(bool value): 0xC77074
    void (*set_active)(void*, char) = (void*)getRealOffset(0xC77074);
    set_active(gameobj, 0x0); // Set active to false, in theory
    log("Attempting to add component for TextMeshProUGUI...");
    // GameObject.AddComponent: 0xC766D0, 0x5BCDA4
    void* (*add_comp)(void*, void*) = (void*)getRealOffset(0xC766D0);
    void* textMesh = add_comp(gameobj, /*TYPE OF TEXTMESHPROUGUI */0);
    //TODO ADD FONT
    log("Attempting to get RectTransform...");
    // TextMeshProUGUI.get_rectTransform: (base class, TMP_Text): 0x50FF0C
    void* (*get_rectTransform)(void*) = (void*)getRealOffset(0x50FF0C);
    void* rectTransform = get_rectTransform(textMesh);
    log("Attempting to set RectTransform parent...");
    // RectTransform.SetParent: (base class, Transform): 0xBEF560
    void (*setParent)(void*, void*, char) = (void*)getRealOffset(0xBEF560);
    setParent(rectTransform, rectTransformParent, 0x0); // Set save world pos to false, in theory
    log("Attempting to get original text...");
    // TextMeshProUGUI.get_text: (base class, TMP_Text): 0x510D88
    cs_string* (*get_text)(void*) = (void*)getRealOffset(0x510D88);
    cs_string* new_text = get_text(textMesh);
    log("Attempting to convert input text: %s", text);
    // Need to call the setter? hopefully just the getter...
    strcpy(new_text->str, text);
    log("Attempting to set font size...");
    // TextMeshProUGUI.set_fontSize: (base class, TMP_Text): 0x5119A8
    void (*set_fontSize)(void*, float) = (void*)getRealOffset(0x5119A8);
    set_fontSize(textMesh, 4.0f);
    // ENTER THE DANGER ZONE!
    log("Attempting to set color to white...");
    // TextMeshProUGUI.set_color: (base class, TMP_Text): 0x51126C
    void (*set_color)(void*, Color) = (void*)getRealOffset(0x51126C);
    set_color(textMesh, (Color){1.0f, 1.0f, 1.0f, 1.0f});

    log("Attempting to set RectTransform.anchorMin...");
    // RectTransform.get_anchorMin: 0xC93240 RETURNS STRUCT? STRUCT POINTER?
    Vector2* (*get_anchorMin)(void*) = (void*)getRealOffset(0xC93240);
    Vector2* m_min = get_anchorMin(rectTransform);
    log("Attempting to set fields for RectTransform.anchorMin...");
    m_min->x = 0.5f;
    m_min->y = 0.5f;
    log("Attempting to set RectTransform.anchorMax...");
    // RectTransform.get_anchorMax: 0xC93398 RETURNS STRUCT? STRUCT POINTER?
    Vector2* (*get_anchorMax)(void*) = (void*)getRealOffset(0xC93398);
    Vector2* m_max = get_anchorMax(rectTransform);
    log("Attempting to set fields for RectTransform.anchorMax...");
    m_max->x = 0.5f;
    m_max->y = 0.5f;
    log("Attempting to set RectTransform.sizeDelta...");
    // RectTransform.set_sizeDelta: 0xC93704 REQUIRES STRUCT? STRUCT POINTER?
    void (*set_sizeDelta)(void*, Vector2) = (void*)getRealOffset(0xC93704);
    set_sizeDelta(rectTransform, sizeDelta);
    log("Attempting to set RectTransform.anchoredPosition...");
    // RectTransform.set_anchoredPosition: 0xC935AC REQUIRES STRUCT? STRUCT POINTER?
    void (*set_anchoredPosition)(void*, Vector2) = (void*)getRealOffset(0xC935AC);
    set_anchoredPosition(rectTransform, anchoredPosition);

    log("Attempting to set game object to be active again...");
    set_active(gameobj, 0x1);
    return textMesh;
}

__attribute__((constructor)) void lib_main()
{
    log("Installing Most-Bestest-Song hooks...");
    
}