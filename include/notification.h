#pragma once
#include <stdlib.h>
#include <string.h>
#include <string_view>
#include "../extern/beatsaber-hook/shared/utils/logging.h"
#include "../extern/beatsaber-hook/shared/customui/customui.hpp"
#include "utils.hpp"
#include <unistd.h>
#include <queue>

// Macros:
// DEBUG_NOTIFICATIONS:
// If enabled, will replace all pushNotification calls with macros that perform the same, with added metadata.
// messages displayed will also contain this metadata.

class NotificationBox {
    public:
        CustomUI::TextObject notificationBox;
        // Initializes the various fields of the notification box. Should be called assuming all values are valid.
        // Must be called before createNotificationBox
        void init(Vector2 anchoredPosition, Vector2 anchorMax, Vector2 anchorMin, Color color, float fontSize, Il2CppObject* parentTransform, Vector2 sizeDelta);
        // Initializes the notification box, assuming the user has already initialized the fields they desire.
        // Must be called before createNotificationBox
        void init();


        // Creates the notification box. Should be called in such a time and place that it is considered valid to create.
        // Returns true on success.
        bool create();

        // To be called relatively frequently
        // such that notifications can be cleared and added within reasonable similarity to their actual duration.
        // Should not be called after markInvalid is set, but will not cause any faults.
        // Common methods to hook for this may include (assuming createNotificationBox has been called within the main menu scene ONLY!):
        // - VRUIControllers.VRInputModule::ProcessMousePress(Il2CppObject* data) which is called any time a button is clicked
        // - VRUIControllers.VRPointer::Process() which is called any time the cursor moves
        // If this function fails to set the text, calls ASSERT_MSG
        void parallelUpdate();

        // To be called at least as frequently as the text object is invalidated.
        // This should occur on scene transitions and should ALWAYS be called any time the text is considered invalid.
        // This function can be called more often than it is actually invalidated (for example, every mouse press)
        // but MUST be called every time the object is invalidated.
        // Calling it redundantly comes at the cost of some performance, but is otherwise safe.
        // If this function fails to destroy the object, calls ASSERT_MSG
        void markInvalid();

        #ifndef DEBUG_NOTIFICATION

        // Pushes a notification at the current time with metadata to be displayed when possible.
        // The notifications are popped in FIFO order, each with duration at least what is specified, 
        // assuming markInvalid is not called while a message is being displayed.
        // Duration is in seconds
        void pushNotification(std::string_view msg, uint duration = 5, const char* func = "unknown", const char* file = "unknown", int line = -1);

        #else

        void _pushNotification(std::string_view msg, uint duration, const char* func, const char* file, int line);
        #define pushNotification(msg, duration = 5) _pushNotification(msg, duration, __PRETTY_FUNCTION__, __FILE__, __LINE__)

        #endif
    private:
        typedef struct message {
            std::string msg;
            std::chrono::system_clock::time_point time;
            uint duration;
        } message_t;

        bool initialized = false;
        bool notificationBoxValid = false;
        std::queue<message_t> cachedMessages;
        message_t current;
        // Possible syncronization issues with these?
        std::chrono::system_clock::time_point messageDisplayed;
        std::chrono::system_clock::time_point messageEnd;

        message_t popNotification();
        void setMessage();
};
