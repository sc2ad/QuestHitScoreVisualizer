#include "beatsaber-hook/shared/utils/logging.hpp"
#include "../include/utils.hpp"
#include "../include/config.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/allocators.h"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

bool requires_text(DisplayMode_t d) {
    return (d & 0b1) != 0;
}

bool requires_image(DisplayMode_t d) {
    return (d & 0b10) != 0;
}

// TODO: Make these definable interfaces

#define GET(obj, fieldName, method, required) auto itr = obj.FindMember(fieldName.data()); \
if (itr == obj.MemberEnd()) { \
    if (required) { \
        getLogger().warning("Failed to find required field: %s! Could not load config", fieldName.data()); \
    } \
    return std::nullopt; \
} \
return itr->value.method()

std::optional<const int> getInt(rapidjson::Value& obj, std::string_view fieldName, bool required) {
    GET(obj, fieldName, GetInt, required);
}

std::optional<float> getFloat(rapidjson::Value& obj, std::string_view fieldName, bool required) {
    GET(obj, fieldName, GetFloat, required);
}

std::optional<const char*> getString(rapidjson::Value& obj, std::string_view fieldName, bool required) {
    GET(obj, fieldName, GetString, required);
}

std::optional<TokenizedText> getTokenizedText(rapidjson::Value& obj, std::string_view fieldName, bool required) {
    auto itr = obj.FindMember(fieldName.data());
    if (itr == obj.MemberEnd()) {
        if (required) {
            getLogger().warning("Failed to find required field: %s! Could not load config", fieldName.data());
        }
        return std::nullopt;
    }
    return TokenizedText(std::string(itr->value.GetString()));
}

std::optional<bool> getBool(rapidjson::Value& obj, std::string_view fieldName, bool required) {
    GET(obj, fieldName, GetBool, required);
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

void judgment::SetImage(std::string imagePath, int threshold) {
    if (this->threshold != threshold)
        this->threshold = threshold;
    this->imagePath.emplace(imagePath);
}

void judgment::SetText(std::string text, Color color, int threshold, bool fade) {
    if (this->threshold != threshold)
        this->threshold = threshold;
    this->tokenizedText.emplace(TokenizedText(text));
    this->color.emplace(color);
    this->fade.emplace(fade);
}

// Returns true on success, false if any segment is invalid (thus the config is invalid)
bool getSegments(std::vector<segment>& out, ConfigDocument& config, std::string_view fieldName, DisplayMode_t displayMode) {
    static auto logger = getLogger().WithContext("Config").WithContext("getSegments");
    auto itr = config.FindMember(fieldName.data());
    if (itr == config.MemberEnd()) {
        logger.warning("Failed to find required field: %s! Could not load config", fieldName.data());
        return false;
    }
    auto arr = itr->value.GetArray();
    auto size = arr.Size();
    for (int i = 0; i < size; i++) {
        auto& currentValue = arr[i];
        segment toAdd;

        if (auto thresh = getInt(currentValue, "threshold")) {
            toAdd.threshold = *thresh;
        }
        toAdd.text = getString(currentValue, "text");
        toAdd.imagePath = getString(currentValue, "imagePath");
        
        // If text is required but not provided, fail
        if (requires_text(displayMode) && !toAdd.text) {
            logger.error("Config could not be loaded! displayMode: %d requires text, but segment: %d had none!", displayMode, i);
            return false;
        }
        // If an image is required but not provided AND no fallback text is available, fail
        // This will bring attention to image only displays failing to have images for all text
        // TODO: Segments do not have text yet!
        // if (requires_image(displayMode) && !toAdd.imagePath) {
        //     if (requires_text(displayMode) && toAdd.text) {
        //         logger.warning("Attempted to load image from: displayMode: %d, but segment: %d had none!", displayMode, i);
        //         logger.info("Will not use an image for this segment");
        //     } else {
        //         logger.warning("Config could not be loaded! displayMode: %d requires an image, but segment: %d had none!", displayMode, i);
        //         return false;
        //     }
        // }
        // Redundant failsafe, should never occur
        if (!toAdd.text && !toAdd.imagePath) {
            logger.error("Config could not be loaded! Missing text and image for segment: %d", i);
            return false;
        }
        out.push_back(toAdd);
    }
    return true;
}

bool getJudgments(std::vector<judgment>& out, ConfigDocument& obj, DisplayMode_t displayMode) {
    static auto logger = getLogger().WithContext("Config").WithContext("getJudgments");
    auto itr = obj.FindMember("judgments");
    if (itr == obj.MemberEnd()) {
        logger.warning("Failed to find required field: judgments! Could not load config");
        return false;
    }
    auto arr = itr->value.GetArray();
    auto size = arr.Size();
    for (int i = 0; i < size; i++) {
        auto& currentValue = arr[i];
        auto& toAdd = out.emplace_back();
        if (auto thresh = getInt(currentValue, "threshold")) {
            toAdd.threshold = *thresh;
        }
        toAdd.tokenizedText = getTokenizedText(currentValue, "text");
        toAdd.imagePath = getString(currentValue, "imagePath");
        toAdd.soundPath = getString(currentValue, "soundPath");
        toAdd.soundVolume = getFloat(currentValue, "soundVolume");
        toAdd.fade = getBool(currentValue, "fade");

        auto itr = currentValue.FindMember("color");
        if (itr != currentValue.MemberEnd()) {
            auto size = itr->value.GetArray().Size();
            if (size == COLOR_ARRAY_LENGTH) {
                auto arr = itr->value.GetArray();
                Color c = {arr[0].GetFloat(), arr[1].GetFloat(), arr[2].GetFloat(), arr[3].GetFloat()};
                toAdd.color.emplace(c);
            } else {
                toAdd.color = std::nullopt;
            }
        } else {
            toAdd.color = std::nullopt;
        }

        // If text is required but not provided, fail
        if (requires_text(displayMode) && !toAdd.tokenizedText) {
            logger.error("Config could not be loaded! displayMode: %d requires text, but judgment: %d had none!", displayMode, i);
            return false;
        }
        // If color is not provided, revert to default color.
        if (requires_text(displayMode) && !toAdd.color) {
            logger.warning("Could not load color for judgment: %d, using white!", i);
            toAdd.color.emplace((Color){0.0f, 0.0f, 0.0f, 0.0f});
        }
        // If an image is required but not provided AND no fallback text is available, fail
        // This will bring attention to image only displays failing to have images for all judgments
        if (requires_image(displayMode) && !toAdd.imagePath) {
            if (requires_text(displayMode) && toAdd.tokenizedText) {
                logger.warning("Attempted to load image from: displayMode: %d, but judgment: %d had none!", displayMode, i);
                logger.info("Will not use an image for this judgment");
                if (!toAdd.color) {
                    logger.info("Using default color!");
                    toAdd.color.emplace((Color){0.0f, 0.0f, 0.0f, 0.0f});
                }
            } else {
                logger.warning("Config could not be loaded! displayMode: %d requires an image, but judgment: %d had none!", displayMode, i);
                return false;
            }
        }
        // Redundant failsafe, should never occur
        if (!toAdd.tokenizedText && !toAdd.imagePath) {
            logger.warning("Config could not be loaded! Missing text and image for judgment: %d", i);
            return false;
        }
    }
    return true;
}

bool HSVConfig::VersionLessThanEqual(int major, int minor, int patch) {
    return major > majorVersion || (major == majorVersion && (minor > minorVersion || (minor == minorVersion && patch >= patchVersion)));
}

bool HSVConfig::VersionGreaterThanEqual(int major, int minor, int patch) {
    return major < majorVersion || (major == majorVersion && (minor < minorVersion || (minor == minorVersion && patch <= patchVersion)));
}

void ConfigHelper::AddJSONJudgment(rapidjson::MemoryPoolAllocator<>& allocator, rapidjson::Document::ValueType& arr, judgment& j) {
    static auto logger = getLogger().WithContext("Config").WithContext("AddJSONJudgment");
    rapidjson::Value v(rapidjson::kObjectType);
    v.AddMember("threshold", j.threshold, allocator);
    if (j.tokenizedText) {
        auto text = j.tokenizedText->original.c_str();
        logger.debug("Adding text field: %s", text);
        v.AddMember("text", rapidjson::GenericStringRef<char>(text), allocator);
    }
    if (j.color) {
        rapidjson::Document::ValueType color(rapidjson::kArrayType);
        color.PushBack(j.color->r, allocator);
        color.PushBack(j.color->g, allocator);
        color.PushBack(j.color->b, allocator);
        color.PushBack(j.color->a, allocator);
        v.AddMember("color", color, allocator);
    }
    if (j.fade) {
        v.AddMember("fade", *j.fade, allocator);
    }
    if (j.imagePath) {
        v.AddMember("imagePath", rapidjson::GenericStringRef<char>(j.imagePath->data()), allocator);
    }
    if (j.soundPath) {
        v.AddMember("soundPath", rapidjson::GenericStringRef<char>(j.soundPath->data()), allocator);
    }
    if (j.soundVolume) {
        v.AddMember("soundVolume", *j.soundVolume, allocator);
    }
    arr.PushBack(v, allocator);
}

void ConfigHelper::AddJSONSegment(rapidjson::Document::AllocatorType& allocator, rapidjson::Document::ValueType& arr, segment& s) {
    rapidjson::Value v(rapidjson::kObjectType);
    v.AddMember("threshold", s.threshold, allocator);
    if (s.text) {
        v.AddMember("text", rapidjson::GenericStringRef<char>(*s.text), allocator);
    }
    if (s.imagePath) {
        v.AddMember("imagePath", rapidjson::GenericStringRef<char>(s.imagePath->data()), allocator);
    }
    arr.PushBack(v, allocator);
}

void ConfigHelper::BackupConfig(ConfigDocument& config, std::string_view newPath) {
    rapidjson::StringBuffer buf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
    config.Accept(writer);
    writefile(newPath.data(), buf.GetString());
}

void ConfigHelper::RestoreConfig(std::string_view newPath) {
    writefile(Configuration::getConfigFilePath(getModInfo()).data(), readfile(newPath.data()));
    getConfig().Reload();
}

void ConfigHelper::CreateJSONSegments(rapidjson::MemoryPoolAllocator<>& allocator, ConfigDocument& config, std::vector<segment>& vector, std::string_view name) {
    auto arr = rapidjson::Value(rapidjson::kArrayType);
    for (auto itr = vector.begin(); itr != vector.end(); ++itr) {
        ConfigHelper::AddJSONSegment(allocator, arr, *itr);
    }
    config.AddMember(rapidjson::GenericStringRef<char>(name.data()), arr, allocator);
}

bool ConfigHelper::LoadConfig(HSVConfig& con, ConfigDocument& config) {
    if (!config.IsObject()) {
        con.SetToDefault();
        return true;
    }
    static auto logger = getLogger().WithContext("ConfigHelper").WithContext("LoadConfig");
    // Default to true.
    // This allows us to forcibly regenerate the config if it doesn't load properly and doesn't have this property.
    con.isDefaultConfig = getBool(config, "isDefaultConfig").value_or(true);
    con.majorVersion = RET_F_UNLESS(logger, getInt(config, "majorVersion", true));
    con.minorVersion = RET_F_UNLESS(logger, getInt(config, "minorVersion", true));
    con.patchVersion = RET_F_UNLESS(logger, getInt(config, "patchVersion", true));
    con.displayMode = convertDisplayMode(RET_F_UNLESS(logger, getString(config, "displayMode", true)));

    RET_F_UNLESS(logger, getJudgments(con.judgments, config, con.displayMode));
    RET_F_UNLESS(logger, getSegments(con.beforeCutAngleJudgments, config, "beforeCutAngleJudgments", con.displayMode));
    RET_F_UNLESS(logger, getSegments(con.accuracyJudgments, config, "accuracyJudgments", con.displayMode));
    RET_F_UNLESS(logger, getSegments(con.afterCutAngleJudgments, config, "afterCutAngleJudgments", con.displayMode));

    // Default to standard type
    con.type = (ConfigType_t)getInt(config, "type").value_or(CONFIG_TYPE_STANDARD);
    // Default to true
    con.useSeasonalThemes = getBool(config, "useSeasonalThemes").value_or(true);
    // Default to true
    con.backupBeforeSeason = getBool(config, "backupBeforeSeason").value_or(true);
    // Default to true
    con.restoreAfterSeason = getBool(config, "restoreAfterSeason").value_or(true);
    // Default to false
    con.useFixedPos = getBool(config, "useFixedPos").value_or(false);
    // Default to 0
    con.fixedPosX = getFloat(config, "fixedPosX").value_or(0);
    con.fixedPosY = getFloat(config, "fixedPosY").value_or(0);
    con.fixedPosZ = getFloat(config, "fixedPosZ").value_or(0);
    // Default to true
    con.doIntermediateUpdates = getBool(config, "doIntermediateUpdates").value_or(true);
    // Default to false
    con.showInitialScore = getBool(config, "showInitialScore").value_or(false);
    return true;
}

void HSVConfig::WriteToConfig(ConfigDocument& config) {
    static auto logger = getLogger().WithContext("HSVConfig").WithContext("WriteToConfig");
    logger.debug("Starting to write to config");
    config.SetObject();
    config.RemoveAllMembers();
    rapidjson::MemoryPoolAllocator<>& allocator = config.GetAllocator();
    // Add versions
    config.AddMember("majorVersion", majorVersion, allocator);
    config.AddMember("minorVersion", minorVersion, allocator);
    config.AddMember("patchVersion", patchVersion, allocator);
    auto arr = rapidjson::Value(rapidjson::kArrayType);
    logger.debug("Starting judgments");
    logger.debug("judgments length: %lu", judgments.size());
    // Add judgments
    for (auto itr = judgments.begin(); itr != judgments.end(); ++itr) {
        logger.debug("judgment: %i", itr->threshold);
        ConfigHelper::AddJSONJudgment(allocator, arr, *itr);
    }
    config.AddMember("judgments", arr, allocator);
    // Add segments
    logger.debug("Starting segments");
    ConfigHelper::CreateJSONSegments(allocator, config, beforeCutAngleJudgments, "beforeCutAngleJudgments");
    ConfigHelper::CreateJSONSegments(allocator, config, accuracyJudgments, "accuracyJudgments");
    ConfigHelper::CreateJSONSegments(allocator, config, afterCutAngleJudgments, "afterCutAngleJudgments");
    // Set metadata
    logger.debug("Starting metadata");
    config.AddMember("type", type, allocator); // Type can be: 0: Standard, 1: Christmas, 2: Easter, etc.
    config.AddMember("useSeasonalThemes", useSeasonalThemes, allocator);
    config.AddMember("backupBeforeSeason", backupBeforeSeason, allocator);
    config.AddMember("restoreAfterSeason", restoreAfterSeason, allocator);
    config.AddMember("displayMode", rapidjson::GenericStringRef<char>(convertDisplayMode(displayMode)), allocator);
    config.AddMember("useFixedPos", useFixedPos, allocator);
    config.AddMember("fixedPosX", fixedPosX, allocator);
    config.AddMember("fixedPosY", fixedPosY, allocator);
    config.AddMember("fixedPosZ", fixedPosZ, allocator);
    config.AddMember("doIntermediateUpdates", doIntermediateUpdates, allocator);
    config.AddMember("showInitialScore", showInitialScore, allocator);
    config.AddMember("isDefaultConfig", isDefaultConfig, allocator);
    logger.debug("Complete!");
}

void HSVConfig::SetToDefault() {
    majorVersion = 2;
    minorVersion = 4;
    patchVersion = 4;
    judgments = std::vector<judgment>(6);
    judgments[0].SetText("%BFantastic%A%n%s", {1.0f, 1.0f, 1.0f, 1.0f}, 115);
    judgments[1].SetText("<size=80%>%BExcellent%A</size>%n%s", {0.0f, 1.0f, 0.0f, 1.0f}, 101);
    judgments[2].SetText("<size=80%>%BGreat%A</size>%n%s", {1.0f, 0.980392158f, 0.0f, 1.0f}, 90);
    judgments[3].SetText("<size=80%>%BGood%A</size>%n%s", {1.0f, 0.6f, 0.0f, 1.0f}, 80, true);
    judgments[4].SetText("<size=80%>%BDecent%A</size>%n%s", {1.0f, 0.0f, 0.0f, 1.0f}, 60, true);
    judgments[5].SetText("<size=80%>%BWay Off%A</size>%n%s", {0.5f, 0.0f, 0.0f, 1.0f}, 0, true);
    beforeCutAngleJudgments = std::vector<segment>(2);
    beforeCutAngleJudgments[0].SetText("+", 70);
    beforeCutAngleJudgments[1].SetText(" ");
    accuracyJudgments = std::vector<segment>(2);
    accuracyJudgments[0].SetText("+", 15);
    accuracyJudgments[1].SetText(" ");
    afterCutAngleJudgments = std::vector<segment>(2);
    afterCutAngleJudgments[0].SetText("+", 30);
    afterCutAngleJudgments[1].SetText(" ");
    displayMode = DISPLAY_MODE_FORMAT;
    useFixedPos = false;
    fixedPosX = 0;
    fixedPosY = 0;
    fixedPosZ = 0;
    doIntermediateUpdates = true;
    showInitialScore = false;
    type = CONFIG_TYPE_STANDARD;
    useSeasonalThemes = true;
    backupBeforeSeason = true;
    restoreAfterSeason = true;
    isDefaultConfig = true;
}

void HSVConfig::SetToSeason(ConfigType_t type) {
    // TODO: Download seasonal config from github
    getLogger().info("Seasons are not yet supported!");
}

void getSegmentImages(std::vector<std::string>& v, std::vector<segment> segs) {
    for (auto s : segs) {
        if (s.imagePath) {
            v.emplace_back(*s.imagePath);
        }
    }
}

std::vector<std::string> HSVConfig::GetAllImagePaths() const {
    std::vector<std::string> v;
    for (auto j : judgments) {
        if (j.imagePath) {
            v.emplace_back(*j.imagePath);
        }
    }
    getSegmentImages(v, beforeCutAngleJudgments);
    getSegmentImages(v, afterCutAngleJudgments);
    getSegmentImages(v, accuracyJudgments);
    return v;
}

std::vector<std::string> HSVConfig::GetAllSoundPaths() const {
    std::vector<std::string> v;
    for (auto j : judgments) {
        if (j.soundPath) {
            v.emplace_back(*j.soundPath);
        }
    }
    return v;
}

// TODO: Revive
// void HSVConfig::SetToChristmas() {
//     // Either download the config from somewhere (could be neat)
//     // Or, Set it directly
//     // Save these parameters to restore
//     majorVersion = 2;
//     minorVersion = 4;
//     patchVersion = 0;
//     judgments = std::vector<judgment>(5);
//     ConfigHelper::Createjudgment(judgments, 0, 115, "MERRY!\n%s", {1.0, 1.0, 1.0, 1.0});
//     ConfigHelper::Createjudgment(judgments, 1, 101, "<size=80%>Arsenic Sauce</size>\n%s", {0.0, 1.0, 0.0, 1.0});
//     ConfigHelper::Createjudgment(judgments, 2, 90, "<size=50%>You're a mean one, Mr. Grinch\nYou really are a heel\nYou're as cuddly as a cactus\nYou're as charming as an eel\nMr. Grinch\nYou're a bad banana with a greasy black peel\nYou're a monster, Mr. Grinch\nYour heart's an empty hole\nYour brain is full of spiders\nYou've got garlic in your soul, Mr Grinch\nI wouldn't touch you with a\nThirty-nine and a half foot pole\nYou're a vile one, Mr. Grinch\nYou have termites in your smile\nYou have all the tender sweetness of a seasick crocodile\nMr Grinch\nGiven the choice between the two of you\nI'd take the seasick crocodile\nYou're a foul one, Mr. Grinch\nYou're a nasty wasty skunk\nYour heart is full of unwashed socks\nYour soul is full of gunk\nMr Grinch\nThe three best words that best describe you\nAre as follows, and I quote\nStink\nStank\nStunk\nYou're a rotter Mr Grinch\nYou're the king of sinful sots\nYour heart's a dead tomato splotched with moldy purple spots\nMr Grinch\nYour soul is an appalling dump heap\nOverflowing with the most disgraceful\nAssortment of deplorable rubbish imaginable\nMangled up in tangled up knots\nYou nauseate me, Mr Grinch\nWith a nauseous super nos\nYou're a crooked jerky jockey and\nYou drive a crooked horse\nMr Grinch\nYou're a three-decker sauerkraut\nAnd toadstool sandwich\nWith arsenic sauce</size>\n%s", {1.0, 0.0, 0.0, 1.0});
//     ConfigHelper::Createjudgment(judgments, 3, 80, "<size=80%>Sot</size>\n%s", {0.7, 0.0, 0.0, 1.0}, true);
//     ConfigHelper::Createjudgment(judgments, 4, 0, "<size=180%>GREASY!</size>", {0.5, 0.0, 0.0, 1.0}, true);
//     beforeCutAnglejudgments = std::vector<segment>(0);
//     accuracyjudgments = std::vector<segment>(0);
//     afterCutAnglejudgments = std::vector<segment>(0);
//     // Add particle effects
//     // COMING SOON
//     // Add UI effects
//     // COMING SOON
//     type = CONFIG_TYPE_CHRISTMAS;
//     backupBeforeSeason = false;
//     displayMode = DISPLAY_MODE_FORMAT;
// }