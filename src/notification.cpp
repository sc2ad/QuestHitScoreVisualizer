#ifdef NOTIFICATION

#include "../include/utils.hpp"
#include "../include/notification.h"
#include <asm/types.h>
// #include "../extern/customui/shared/customui.hpp"
#include <time.h>
#include <queue>
#include <chrono>

NotificationBox::message_t NotificationBox::popNotification() {
    auto now = std::chrono::system_clock::now();
    if (now < messageEnd) {
        return current;
    }
    if (cachedMessages.empty()) {
        return {"", now, 0};
    }
    auto m = cachedMessages.front();
    cachedMessages.pop();
    current = m;
    return m;
}

void NotificationBox::setMessage() {
    static auto logger = getLogger().WithContext("NotificationBox").WithContext("setMessage");
    // If we can, try to pop from the queue
    message_t m = popNotification();
    // If the message we popped is the current message, we don't need to continue
    if (m.time == current.time) {
        return;
    }
    // If we can, try to display the message to the notification box
    if (!notificationBoxValid && !create()) {
        // Failed to send the message! Current is the message we want to display
        // Need to find a way to failsafe this, or otherwise assume we have entered an irrecoverable state.
        return;
    }
    ASSERT_MSG(logger, notificationBox.set(m.msg), "Failed to set text of notificationBox!");
    // If we can, set messageDisplayed to now
    messageDisplayed = std::chrono::system_clock::now();
    messageEnd = messageDisplayed + std::chrono::seconds(m.duration);
}

void NotificationBox::init(Vector2 anchoredPosition, Vector2 anchorMax, Vector2 anchorMin, Color color, float fontSize, Il2CppObject* parentTransform, Vector2 sizeDelta) {
    notificationBox.anchoredPosition = anchoredPosition;
    notificationBox.anchorMax = anchorMax;
    notificationBox.anchorMin = anchorMin;
    notificationBox.color = color;
    notificationBox.fontSize = fontSize;
    notificationBox.parentTransform = parentTransform;
    notificationBox.sizeDelta = sizeDelta;
    initialized = true;
}

void NotificationBox::init() {
    initialized = true;
}

bool NotificationBox::create() {
    // Try to create notification box
    if (!initialized) {
        notificationBoxValid = false;
        return false;
    }
    notificationBoxValid = notificationBox.create();
    return notificationBoxValid;
}

void NotificationBox::pushNotification(std::string_view msg, uint32_t duration, const char* func, const char* file, int line) {
    message_t m;
    m.time = std::chrono::system_clock::now();
    #ifdef DEBUG_NOTIFICATIONS
    m.msg = std::string(file) + ":" + func + "." + line + ": " + msg;
    #else
    m.msg = msg;
    #endif
    m.duration = duration;
    cachedMessages.push(m);
}

// We want to have a function that ticks
// But, sadly, we can't call anything while on that thread
// So, we want to have a way of rejoining the main thread, but only when we need to actually do something.
// This is a rather tough problem, since we could solve it sloppily via hooking a controller update method
// But the goal is to do this without hooking, hopefully.

// Really, how can we force the main thread to preempt/give us control?
// I think we will have to have a subprocess running in Update that only consumes when it needs to

// This function should only be called when we are in the same scene that the text object exists in.
// It's also possible the instance of the object may have been killed, so remaking it may also be necessary.
void NotificationBox::parallelUpdate() {
    // The gameObj and textMesh pointers may be dangling. In order to detect this, we can attempt to call a method on them.
    // If the method fails, we know we have a dangling pointer (or otherwise invalid object)
    // This is SUPER SLOW since if it causes an exception (probably) it'll have to forward that exception all the way up
    // and let Unity handle it.
    // We could also get around this by forcibly deleting the object whenever it is no longer needed.
    // This would also allow us to reconstruct it on demand much easier, since we know when we have destroyed it.
    // This does require hooking scene transitions (or perhaps just interactions on the main menu)
    if (!notificationBoxValid) {
        // Do nothing if we are not valid
        return;
    }
    // Get local time
    auto now = std::chrono::system_clock::now();
    if (now > messageEnd) {
        // A better approach would be to consider all situations in which the object could be destroyed, and only destroy then
        // Recreating the object IS expensive, and should be avoided.
        // Set the message to the next one available, if it exists.
        setMessage();
    }
}

// Should be called whenever the notificationBox MAY no longer be valid.
// This should be called for all situations in which the notificationBox would be considered invalid
// but it can ALSO be called even if the notificationBox is still valid (at the cost of performance)
void NotificationBox::markInvalid() {
    if (notificationBoxValid) {
        static auto logger = getLogger().WithContext("NotificationBox").WithContext("markInvalid");
        notificationBoxValid = false;
        ASSERT_MSG(logger, notificationBox.destroy(), "Failed to destroy notificationBox!");
    }
}

// Idea: Hook onto VRControllersInputManager.TriggerValue(int node)
// Or: VRUIControllers.VRInputModule::ProcessMousePress(Il2CppObject* data) which is called any time a button is clicked
// Or: VRUIControllers.VRPointer::Process() which is in theory called any time the cursor moves
#endif