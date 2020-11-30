#pragma once
#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include <stddef.h>
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"

Logger& getLogger();
Configuration& getConfig();
const ModInfo& getModInfo();

void safeAbort(const char* func, const char* file, int line);

template<class T>
auto assertUnlessMessage(T&& arg, LoggerContextObject& logger, const char* func, const char* file, int line, const char* msg) {
    if (!arg) {
        logger.critical("%s", msg);
        safeAbort(func, file, line);
    }
    return std::forward<T>(arg);
}

#ifdef DEBUG
#define ASSERT_MSG(logger, expr, msg) assertUnlessMessage(expr, logger, __PRETTY_FUNCTION__, __FILE__, __LINE__, msg)
#else
#define ASSERT_MSG(logger, expr, msg) assertUnlessMessage(expr, logger, __PRETTY_FUNCTION__, "unknown", __LINE__, msg)
#endif

#define RET_F_UNLESS(logger, ...) RET_UNLESS(false, logger, __VA_ARGS__)
