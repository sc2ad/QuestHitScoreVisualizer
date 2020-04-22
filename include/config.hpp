#pragma once
#define RAPIDJSON_HAS_STDSTRING 1
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/logging.h"

// Requires text: & 0b1
// Requires image: & 0b10
typedef enum DisplayMode {
    DISPLAY_MODE_NUMERIC = 0b00,
    DISPLAY_MODE_TEXTONLY = 0b01,
    DISPLAY_MODE_IMAGEONLY = 0b10,
    DISPLAY_MODE_IMAGEANDTEXT = 0b11,
    DISPLAY_MODE_FORMAT = 0b101,
    DISPLAY_MODE_SCOREONTOP = 0b1001,
    DISPLAY_MODE_TEXTONTOP = 0b1101
} DisplayMode_t;

bool requires_text(DisplayMode_t d) {
    return (d & 0b1) != 0;
}

bool requires_image(DisplayMode_t d) {
    return (d & 0b10) != 0;
}

typedef enum ConfigType {
    CONFIG_TYPE_STANDARD,
    CONFIG_TYPE_CHRISTMAS,
    CONFIG_TYPE_EASTER
} ConfigType_t;

#define COLOR_ARRAY_LENGTH 4

// TODO: Make these definable interfaces

#define GET(obj, fieldName, method, required) auto itr = obj.FindMember(fieldName.data()); \
if (itr == obj.MemberEnd()) { \
    if (required) { \
        log(WARNING, "Failed to find required field: %s! Could not load config", fieldName.data()); \
    } \
    return std::nullopt; \
} \
return itr->value.method()

#define GET_VAL(obj, fieldName, required) auto itr = obj.FindMember(fieldName.data()); \
if (itr == obj.MemberEnd()) { \
    if (required) { \
        log(WARNING, "Failed to find required field: %s! Could not load config", fieldName.data()); \
    } \
    return std::nullopt; \
} \
return itr->value

std::optional<const int&> getInt(rapidjson::Value& obj, std::string_view fieldName, bool required = false) {
    GET(obj, fieldName, GetInt, required);
}

std::optional<float&> getFloat(rapidjson::Value& obj, std::string_view fieldName, bool required = false) {
    GET(obj, fieldName, GetFloat, required);
}

std::optional<const char*> getString(rapidjson::Value& obj, std::string_view fieldName, bool required = false) {
    GET(obj, fieldName, GetString, required);
}

std::optional<bool&> getBool(rapidjson::Value& obj, std::string_view fieldName, bool required = false) {
    GET(obj, fieldName, GetBool, required);
}

std::optional<rapidjson::Value&> getValue(rapidjson::Value& obj, std::string_view fieldName, bool required = false) {
    GET_VAL(obj, fieldName, required);
}

const char* convertDisplayMode(DisplayMode displayMode) {
    switch (displayMode) {
        case DISPLAY_MODE_FORMAT:
            return "format";
        case DISPLAY_MODE_NUMERIC:
            return "numeric";
        case DISPLAY_MODE_SCOREONTOP:
            return "scoreOnTop";
        case DISPLAY_MODE_TEXTONLY:
            return "textOnly";
        case DISPLAY_MODE_TEXTONTOP:
            return "textOnTop";
        case DISPLAY_MODE_IMAGEONLY:
            return "imageOnly";
        case DISPLAY_MODE_IMAGEANDTEXT:
            return "imageAndText";
    }
    return "UNKNOWN";
}

DisplayMode convertDisplayMode(std::string_view displayMode) {
    if (displayMode == "format") {
        return DISPLAY_MODE_FORMAT;
    } else if (displayMode == "numeric") {
        return DISPLAY_MODE_NUMERIC;
    } else if (displayMode == "scoreOnTop") {
        return DISPLAY_MODE_SCOREONTOP;
    } else if (displayMode == "textOnly") {
        return DISPLAY_MODE_TEXTONLY;
    } else if (displayMode == "textOnTop") {
        return DISPLAY_MODE_TEXTONTOP;
    } else if (displayMode == "imageOnly") {
        return DISPLAY_MODE_IMAGEONLY;
    } else if (displayMode == "imageAndText") {
        return DISPLAY_MODE_IMAGEANDTEXT;
    }
    // Otherwise, display in default format
    return DISPLAY_MODE_TEXTONTOP;
}

class judgment {
    public:
        // Threshold that the score must be greater than or equal to.
        int threshold;
        // HSV specific text to display.
        // Supports TMP text and % operators.
        std::optional<std::string> text;
        // A vector of length COLOR_ARRAY_LENGTH for the color.
        // If the length is not the same, the color is ignored.
        std::optional<std::vector<float>> color;
        // Whether to fade between colors, if possible.
        std::optional<bool> fade;
        // Optional path to an image (ignores text, color, and fade fields).
        std::optional<std::string> imagePath;

        void SetText(std::string text, std::vector<float>& color, int threshold = 0, bool fade = false) {
            if (this->threshold != threshold)
                this->threshold = threshold;
            this->text.emplace(text);
            this->color.emplace(color);
            this->fade.emplace(fade);
        }
        void SetImage(std::string imagePath, int threshold = 0) {
            if (this->threshold != threshold)
                this->threshold = threshold;
            this->imagePath.emplace(imagePath);
        }
        judgment();
};

class segment {
    public:
        // Threshold that the score portion must be greater than or equal to.
        int threshold;
        // TMP text to display.
        std::optional<const char*> text;
        // Optional path to an image.
        std::optional<std::string> imagePath;

        void SetText(const char* text, int threshold = 0) {
            if (this->threshold != threshold)
                this->threshold = threshold;
            this->text.emplace(text);
        }
        void SetImage(std::string imagePath, int threshold = 0) {
            if (this->threshold != threshold)
                this->threshold = threshold;
            this->imagePath.emplace(imagePath);
        }
        segment();
};

class HSVConfig {
    public:
        // Major version of the config.
        int majorVersion;
        // Minor version of the config.
        int minorVersion;
        // Patch version of the config.
        int patchVersion;
        // True: Will cause the config to be overwritten on updates
        bool isDefaultConfig;
        // Display mode of the visualization.
        // Must be one of the following:
        // "format"
        // "numeric"
        // "textOnly"
        // "scoreOnTop"
        // "textOnTop"
        // "imageOnly" If an image exists, otherwise: format
        // "imageAndText" If an image exists, otherwise: format
        // Otherwise, will display judgment text above the numeric score.
        DisplayMode_t displayMode;
        // True: Will use fixedPosX, fixedPosY, fixedPosZ to anchor the visualization in place.
        // Works for images.
        bool useFixedPos;
        // Fixed X Position
        float fixedPosX;
        // Fixed Y Position
        float fixedPosY;
        // Fixed Z Position
        float fixedPosZ;
        // True: Will perform intermediate updates to ensure a correct value at the cost of performance
        bool doIntermediateUpdates;

        std::vector<judgment> judgments;
        std::vector<segment> beforeCutAngleJudgments;
        std::vector<segment> accuracyJudgments;
        std::vector<segment> afterCutAngleJudgments;

        // Config type
        ConfigType_t type;
        // True: Will change config when a season change occurs
        bool useSeasonalThemes;
        // True: Will backup the config before changing to a new season
        bool backupBeforeSeason;
        // True: Will restore after the season has ended
        bool restoreAfterSeason;

        bool VersionGreaterThanEqual(int major, int minor, int patch);
        bool VersionLessThanEqual(int major, int minor, int patch);
        void WriteToConfig(ConfigDocument& config);
        void SetToDefault();
        void SetToSeason(ConfigType_t type);
    private:
        void SetToChristmas();
        void SetToEaster();
};

class ConfigHelper {
    public:
        static void RestoreConfig(std::string_view newPath);
        static void BackupConfig(ConfigDocument& config, std::string_view newPath);
        static bool LoadConfig(HSVConfig& con, ConfigDocument& config);
        static void AddJSONSegment(rapidjson::Document::AllocatorType& allocator, rapidjson::Document::ValueType& arr, segment& s);
        static void CreateJSONSegments(rapidjson::MemoryPoolAllocator<>& allocator, ConfigDocument& config, std::vector<segment>& vector, std::string_view name);
        static void AddJSONJudgment(rapidjson::MemoryPoolAllocator<>& allocator, rapidjson::Document::ValueType& arr, judgment& j);
};

