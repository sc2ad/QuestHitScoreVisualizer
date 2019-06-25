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

struct Vector2 {
    float x;
    float y;
}

struct textMeshProUGUI {
    // PLACEHOLDER, NO FIELDS OF INTEREST
}

struct rectTransform {
    // PLACEHOLDER, NO FIELDS OF INTEREST
}

void* createText(void* rectTransformParent, char text[], Vector2 anchoredPosition, Vector2 sizeDelta) {
    log("Creating text: %s", text);
    log("Attempting to create new gameobject...");
    // GameObject.ctor(string name): 0xC7643C
    void* gameobj = malloc(sizeof(GameObject)); // YIKES!
    log("Attempting to disable the active state of the gameobject...");
    // GameObject.SetActive(bool value): 0xC77074
    void (*set_active)(void* go, char active) = (void*)getRealOffset(0xC77074);
    set_active(gameobj, 0x0); // Set active to false, in theory
    log("Attempting to add component for TextMeshProUGUI...");
    // GameObject.AddComponent: 0xC766D0, 0x5BCDA4
    textMeshProUGUI* (*add_comp)(void* go, void* type) = (textMeshProUGUI*)getRealOffset(0xC766D0);
    textMeshProUGUI* textMesh = add_comp(gameobj, /*TYPE OF TEXTMESHPROUGUI */0);
    //TODO ADD FONT
    log("Attempting to get RectTransform...");
    // textMesh.get_rectTransform: (base class, TMP_Text): 0x50FF0C
    void* (*get_rectTransform)(void* tmp) = (void*)getRealOffset(0x50FF0C);
    void* rectTransform = get_rectTransform(textMesh);
    log("Attempting to set RectTransform parent...");
    // RectTransform.SetParent: (base class, Transform): 0xBEF560
    void (*setParent)(void* trans, char saveWorldPos) = (void*)getRealOffset(0xBEF560);
    setParent(rectTransform, 0x0); // Set save world pos to false, in theory
    
}

__attribute__((constructor)) void lib_main()
{
    log("Installing Most-Bestest-Song hooks...");
    
}