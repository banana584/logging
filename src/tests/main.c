#define DEBUG_ENABLED
#define LOG_FILE "log.txt"
#include "../../include/logging.h"

int main() {
    ADD_OUTPUT(OUTPUT_FILE);
    ADD_OUTPUT(OUTPUT_PRINT);

    LOG(LEVEL_INFO, "Args %d", 123);

    LOG_CALL(ERROR, "error %d", 1414);

    LOG(LEVEL_INFO, "test noargs");

    LOG_CALL(INFO, "test %d", 321);

    LOG_CALL(DEBUG, "debug");

    return 0;
}