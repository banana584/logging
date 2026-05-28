#include "../include/logging.h"

#define X(name, level) #name,
char* logging_level_names[] = {
    LOGGING_LEVELS(X)
};
#undef X