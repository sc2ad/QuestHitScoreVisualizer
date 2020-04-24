#pragma once

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

bool requires_text(DisplayMode_t d);
bool requires_image(DisplayMode_t d);

typedef enum ConfigType {
    CONFIG_TYPE_STANDARD,
    CONFIG_TYPE_CHRISTMAS,
    CONFIG_TYPE_EASTER
} ConfigType_t;

#define COLOR_ARRAY_LENGTH 4

std::optional<const int> getInt(rapidjson::Value& obj, std::string_view fieldName, bool required = false);
std::optional<float> getFloat(rapidjson::Value& obj, std::string_view fieldName, bool required = false);
std::optional<const char*> getString(rapidjson::Value& obj, std::string_view fieldName, bool required = false);
std::optional<bool> getBool(rapidjson::Value& obj, std::string_view fieldName, bool required = false);

const char* convertDisplayMode(DisplayMode displayMode);

DisplayMode convertDisplayMode(std::string_view displayMode);

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
        // Optional path to an image (ignores text, and fade fields; color is used to tint the image).
        std::optional<std::string> imagePath;
        // Optional path to a sound to play (plays during existing hitSounds)
        std::optional<std::string> soundPath;
        // Optional volume of the sound to play, default of 1.0 volume
        std::optional<float> soundVolume;

        void SetText(std::string text, std::vector<const float> color, int threshold = 0, bool fade = false);
        void SetImage(std::string imagePath, int threshold = 0);
        std::optional<Color> GetColor();
    private:
        // Internal Color
        std::optional<Color> _color;
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

