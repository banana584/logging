#ifndef LIBLOGGING_LOGGING_H
#define LIBLOGGING_LOGGING_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define LOGGING_LEVELS(X) \
    X(DEBUG, LEVEL_DEBUG) \
    X(INFO, LEVEL_INFO) \
    X(WARN, LEVEL_WARN) \
    X(ERROR, LEVEL_ERROR) \
    X(FATAL, LEVEL_FATAL)

typedef enum LoggingLevels {
    #define X(name, level) level,
    LOGGING_LEVELS(X)
    #undef X
} LoggingLevels;

extern char* logging_level_names[];

#define DATETIME_NOW(buf, size) do {             \
    time_t t = time(NULL);                       \
    struct tm* tm_info = localtime(&t);          \
    strftime((buf), (size), "%Y-%m-%d %H:%M:%S", tm_info); \
} while (0)

#define LOG(level, fmt, ...) do {                                                                                  \
    char datetime[64];                                                                                             \
    DATETIME_NOW(datetime, 64);                                                                                    \
    printf("%s [%s:%d] [%s]: " fmt "\n", logging_level_names[level], __FILE__, __LINE__, datetime, ##__VA_ARGS__); \
} while (0)

#define LOG_VLIST(level, fmt, ap) do {                                                                   \
    char datetime[64];                                                                                   \
    DATETIME_NOW(datetime, sizeof(datetime));                                                            \
    char user_msg[512];                                                                                  \
    vsnprintf(user_msg, sizeof(user_msg), fmt, ap);                                                      \
    printf("%s [%s:%d] [%s]: %s\n", logging_level_names[level], __FILE__, __LINE__, datetime, user_msg); \
} while (0)

#define X(name, level) \
static inline void name(const char* fmt, ...) { \
    va_list ap;                                       \
    va_start(ap, fmt);                                \
    LOG_VLIST(level, fmt, ap);                        \
    va_end(ap);                                       \
}
LOGGING_LEVELS(X)
#undef X

#endif