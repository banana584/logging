#ifndef LIBLOGGING_LOGGING_H
#define LIBLOGGING_LOGGING_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

// Each level able to be logged
#define LOGGING_LEVELS(X) \
    X(DEBUG, LEVEL_DEBUG) \
    X(INFO, LEVEL_INFO) \
    X(WARN, LEVEL_WARN) \
    X(ERROR, LEVEL_ERROR) \
    X(FATAL, LEVEL_FATAL)

// Each way of outputting logs
#define LOGGING_OUTPUTS(X) \
    X(PRINT) \
    X(FILE)

// Levels in an enum
typedef enum LoggingLevels {
    #define X(name, level) level,
    LOGGING_LEVELS(X)
    #undef X
} LoggingLevels;

// Outputs in an enum
typedef enum LoggingOutputs {
    #define X(name) OUTPUT_##name,
    LOGGING_OUTPUTS(X)
    #undef X
} LoggingOutputs;

// Names of levels
extern char* logging_level_names[];

// Gets the current time in a format
#define DATETIME_NOW(buf, size) do {                       \
    time_t t = time(NULL);                                 \
    struct tm* tm_info = localtime(&t);                    \
    strftime((buf), (size), "%Y-%m-%d %H:%M:%S", tm_info); \
} while (0)

// Displays a message with level, format and args
#ifdef DEBUG_ENABLED
#define LOG(level, fmt, ...) do {                                                                                  \
    char datetime[64];                                                                                             \
    DATETIME_NOW(datetime, 64);                                                                                    \
    printf("%s [%s:%d] [%s]: " fmt "\n", logging_level_names[level], __FILE__, __LINE__, datetime, ##__VA_ARGS__); \
} while (0)
#else
#define LOG(level, fmt, ...) do {   \
    if (level == LEVEL_DEBUG) break;                                                                                   \
    char datetime[64];                                                                                             \
    DATETIME_NOW(datetime, 64);                                                                                    \
    printf("%s [%s:%d] [%s]: " fmt "\n", logging_level_names[level], __FILE__, __LINE__, datetime, ##__VA_ARGS__); \
} while (0)
#endif

// Displays a message from vlist the same way as the LOG macro
#ifdef DEBUG_ENABLED
#define LOG_VLIST(level, file, line, fmt, ap) do {                                               \
    char datetime[64];                                                                           \
    DATETIME_NOW(datetime, sizeof(datetime));                                                    \
    char user_msg[512];                                                                          \
    vsnprintf(user_msg, sizeof(user_msg), fmt, ap);                                              \
    printf("%s [%s:%d] [%s]: %s\n", logging_level_names[level], file, line, datetime, user_msg); \
} while (0)
#else
#define LOG_VLIST(level, file, line, fmt, ap) do {                                                   \
    if (level == LEVEL_DEBUG) break;                                                                 \
    char datetime[64];                                                                           \
    DATETIME_NOW(datetime, sizeof(datetime));                                                    \
    char user_msg[512];                                                                          \
    vsnprintf(user_msg, sizeof(user_msg), fmt, ap);                                              \
    printf("%s [%s:%d] [%s]: %s\n", logging_level_names[level], file, line, datetime, user_msg); \
} while (0)
#endif

// Calls a log function
#define LOG_CALL(fn, fmt, ...) fn(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

// Generate all functions for logging
#define X(name, level)                                                      \
static inline void name(const char* file, int line, const char* fmt, ...) { \
    va_list ap;                                                             \
    va_start(ap, fmt);                                                      \
    LOG_VLIST(level, file, line, fmt, ap);                                  \
    va_end(ap);                                                             \
}
LOGGING_LEVELS(X)
#undef X

#endif