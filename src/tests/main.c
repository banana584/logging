#include "../../include/logging.h"

int main() {
    LOG(LEVEL_INFO, "Args %d", 123);

    ERROR("error %d", 1414);

    LOG(LEVEL_INFO, "test noargs");

    INFO("test %d", 321);

    return 0;
}