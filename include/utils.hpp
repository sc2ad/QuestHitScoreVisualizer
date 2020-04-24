#pragma once
#include <stddef.h>
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/beatsaber-hook/shared/utils/logging.h"

void safeAbort(const char* func, const char* file, int line);

template<class T>
auto assertUnlessMessage(T&& arg, const char* func, const char* file, int line, const char* msg) {
    if (!arg) {
        log(CRITICAL, "%s", msg);
        safeAbort(func, file, line);
    }
    return std::forward<T>(arg);
}

#define ASSERT_MSG(expr, msg) assertUnlessMessage(expr, __PRETTY_FUNCTION__, __FILE__, __LINE__, msg)

#define RET_F_UNLESS(expr) RET_UNLESS(false, expr)
