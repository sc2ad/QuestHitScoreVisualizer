#pragma once
template<class T>
auto assertUnlessMessage(T&& arg, const char* func, const char* file, int line, const char* msg) {
    if (!arg) {
        log(CRITICAL, msg);
        safeAbort(func, file, line);
    }
    return std::forward<T>(arg);
}
#define ASSERT_MSG(expr, msg) assertUnlessMessage(expr, __PRETTY_FUNCTION__, __FILE__, __LINE__, msg)

#define RET_F_UNLESS(expr) RET_UNLESS(false, expr)

#define min(a, b) (((a) < (b)) ? (a) : (b))
