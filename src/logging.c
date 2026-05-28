#include "../include/logging.h"

#define X(name, level) #name,
char* logging_level_names[] = {
    LOGGING_LEVELS(X)
};
#undef X

#define X(name) #name,
char* logging_output_names[] = {
    LOGGING_OUTPUTS(X)
};
#undef X

LoggingOutputs outputs[OUTPUT_NUM] = { 0 };
size_t num_outputs = 0;