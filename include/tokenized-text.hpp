#pragma once

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <sstream>
#include "utils.hpp"

// Create a setNAME method that reads from the name##Tokens field and sets all tokens listed.
#define __SET_TOKEN(name) \
void set_##name(std::string_view name) { \
    invalidate_text(); \
    for (auto idx : name##Tokens) { \
        tokens[idx] = name; \
    } \
} \
auto get_##name##Tokens_size() { \
    return name##Tokens.size(); \
}

class TokenizedText {
public:
    TokenizedText(std::string str) {
        static auto logger = getLogger().WithContext("TokenizedText");
        // Copy, don't move, str.
        original = str;
        // Parse the string into tokens, converting the string back is easy.
        logger.debug("Tokenizing string: %s", str.c_str());
        std::stringstream ststr;
        int i = 0;
        bool isPercent = false;
        // TODO: Can make this EVEN FASTER by getting a list of indices of where the %'s are ONCE
        // Tokenize this, cache text locations AOT
        // And then replacing the corresponding indices with them as we iterate
        for (auto itr = str.begin(); itr != str.end(); ++itr) {
            auto current = *itr;
            if (isPercent) {
                // If the last character was a %, place index i into our map, key: current
                std::string buffer;
                // Even though emplacing here can cause quite a few resize operations, it's better than using std::list.
                // This is because we need to be able to convert from tokens to a string really quickly.
                // vector is great for that because it is a contigous region of memory.
                if (current == 'n') {
                    tokens.emplace_back("\n");
                } else if (current == '%') {
                    tokens.emplace_back("%");
                } else {
                    // Depending on current, add to a vector of type: current with i
                    switch (current) {
                        case 'b':
                            beforeCutTokens.push_back(i);
                            break;
                        case 'c':
                            cutDistanceTokens.push_back(i);
                            break;
                        case 'a':
                            afterCutTokens.push_back(i);
                            break;
                        case 'B':
                            beforeCutSegmentTokens.push_back(i);
                            break;
                        case 'C':
                            cutDistanceSegmentTokens.push_back(i);
                            break;
                        case 'A':
                            afterCutSegmentTokens.push_back(i);
                            break;
                        case 's':
                            scoreTokens.push_back(i);
                            break;
                        case 'p':
                            percentTokens.push_back(i);
                            break;
                        default:
                            // In the event of an unsupported char, we just tokenize it without populating any of the vectors.
                            // This allows us to keep the % in <size=80%>, since > is not a special char
                            auto str = std::string("%") + current;
                            tokens.push_back(str);
                            logger.debug("Adding non-token for string: %s, index: %u", str.c_str(), i);
                            isPercent = false;
                            i++;
                            continue;
                    }
                }
                logger.debug("Adding token for char: %c, index: %u", current, i);
                tokens.emplace_back("");
                isPercent = false;
                i++;
                continue;
            }
            if (current == '%' && !isPercent) {
                logger.debug("Adding str: %s as non-token!", ststr.str().c_str());
                tokens.emplace_back(ststr.str());
                ststr.str(std::string());
                isPercent = true;
                i++;
            } else {
                ststr.put(current);
            }
        }
        // Add final value to tokens as well
        if (ststr.str().size() != 0) {
            logger.debug("Adding final string: %s", ststr.str().c_str());
            tokens.emplace_back(ststr.str());
        }
    }

    // Get the original string from creation of this
    std::string Raw() {
        static auto logger = getLogger().WithContext("TokenizedText").WithContext("Raw");
        logger.debug("Getting raw original from tokenized text: %s", original.c_str());
        return original;
    }
    // Get the token-joined string from creation of this
    std::string Join() {
        static auto logger = getLogger().WithContext("TokenizedText").WithContext("Join");
        if (!textValid) {
            textValid = true;
            text = std::accumulate(tokens.begin(), tokens.end(), std::string{});
        }
        logger.debug("Joining tokens of size: %u, valid? %c, result text: %s", tokens.size(), textValid ? 't' : 'f', text.c_str());
        return text;
    }

    void invalidate_text() {
        textValid = false;
    }

    __SET_TOKEN(beforeCut)
    __SET_TOKEN(cutDistance)
    __SET_TOKEN(afterCut)
    __SET_TOKEN(beforeCutSegment)
    __SET_TOKEN(cutDistanceSegment)
    __SET_TOKEN(afterCutSegment)
    __SET_TOKEN(score)
    __SET_TOKEN(percent)

    // Original text, should only be used for config write out
    std::string original;
    // All tokens
    std::vector<std::string> tokens;
    private:
    // Is cached text valid? Should be invalidated on tokens change
    bool textValid = false;
    // Cached text, should be invalidated on tokens change
    std::string text;
    // These vectors represent indices of tokens to replace for each token type.
    // This could probably be changed to be a much more dynamic setup, but at the moment, a vector per type is fast.
    std::vector<int> beforeCutTokens;
    std::vector<int> cutDistanceTokens;
    std::vector<int> afterCutTokens;
    std::vector<int> beforeCutSegmentTokens;
    std::vector<int> cutDistanceSegmentTokens;
    std::vector<int> afterCutSegmentTokens;
    std::vector<int> scoreTokens;
    std::vector<int> percentTokens;
};
