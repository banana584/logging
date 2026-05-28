#include "../../include/logging.h"

int main() {
    LOG(LEVEL_INFO, "Args %d", 123);

    LOG_CALL(ERROR, "error %d", 1414);

    LOG(LEVEL_INFO, "test noargs");

    LOG_CALL(INFO, "test %d", 321);

    return 0;
}