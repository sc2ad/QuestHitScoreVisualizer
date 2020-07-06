#pragma once
#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include <stddef.h>
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/beatsaber-hook/shared/config/config-utils.hpp"

const Logger& getLogger();
Configuration& getConfig();
const ModInfo& getModInfo();

void safeAbort(const char* func, const char* file, int line);

template<class T>
auto assertUnlessMessage(T&& arg, const char* func, const char* file, int line, const char* msg) {
    if (!arg) {
        getLogger().critical("%s", msg);
        safeAbort(func, file, line);
    }
    return std::forward<T>(arg);
}

#ifdef DEBUG
#define ASSERT_MSG(expr, msg) assertUnlessMessage(expr, __PRETTY_FUNCTION__, __FILE__, __LINE__, msg)
#else
#define ASSERT_MSG(expr, msg) assertUnlessMessage(expr, __PRETTY_FUNCTION__, "unknown", __LINE__, msg)
#endif

#define RET_F_UNLESS(expr) RET_UNLESS(false, expr)
