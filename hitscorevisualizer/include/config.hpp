#pragma once
#define RAPIDJSON_HAS_STDSTRING 1
#include "../../beatsaber-hook/shared/config/config-utils.hpp"

typedef enum DisplayMode {
    DISPLAY_MODE_FORMAT = 0,
    DISPLAY_MODE_NUMERIC = 1,
    DISPLAY_MODE_TEXTONLY = 2,
    DISPLAY_MODE_SCOREONTOP = 3,
    DISPLAY_MODE_TEXTONTOP = 4
} DisplayMode;

typedef enum ConfigType {
    CONFIG_TYPE_STANDARD = 0,
    CONFIG_TYPE_CHRISTMAS = 1,
    CONFIG_TYPE_EASTER = 2
} ConfigType;

struct judgement {
    int threshold;
    std::string text;
    std::vector<float> color;
    bool fade;
};

struct segment {
    int threshold;
    const char* text;
};

class HSVConfig {
    public:
        int majorVersion;
        int minorVersion;
        int patchVersion;
        std::vector<judgement> judgements;
        std::vector<segment> beforeCutAngleJudgements;
        std::vector<segment> accuracyJudgements;
        std::vector<segment> afterCutAngleJudgements;
        ConfigType type;
        bool useSeasonalThemes;
        bool backupBeforeSeason;
        bool restoreAfterSeason;
        DisplayMode displayMode;

        bool VersionGreaterThanEqual(int major, int minor, int patch);
        bool VersionLessThanEqual(int major, int minor, int patch);
        void WriteToConfig(ConfigDocument& config);
        void SetToDefault();
        void SetToChristmas();
        void SetToEaster();
};

class ConfigHelper {
    public:
        static void RestoreConfig(std::string_view newPath);
        static void BackupConfig(ConfigDocument& config, std::string_view newPath);
        static HSVConfig LoadConfig(ConfigDocument& config);
        static void AddJSONSegment(rapidjson::Document::AllocatorType& allocator, rapidjson::Document::ValueType& arr, segment& s);
        static void CreateJSONSegments(rapidjson::MemoryPoolAllocator<>& allocator, ConfigDocument& config, std::vector<segment>& vector, std::string_view name);
        static void AddJSONJudgement(rapidjson::MemoryPoolAllocator<>& allocator, rapidjson::Document::ValueType& arr, judgement& j);
        static void CreateJudgement(std::vector<judgement>& judgements, int index, int threshold, std::string_view text, std::vector<float> color, bool fade = false);
        static void CreateSegment(std::vector<segment>& segments, int index, int threshold, std::string_view text);
};

