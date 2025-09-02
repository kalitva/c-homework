#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#include "logapi.h"

#define LOG_MESSAGE_FORMAT "%s [%s] '%s' in %s line:%d\n"

logger* log_init_internal(char* filename, log_level level);
void log_clean_internal(logger* logger);

#define LOG(logger, message, level) \
  (log_internal(logger, level, message, __func__, __LINE__))

void log_internal(logger* logger,
    log_level level,
    const char* message,
    const char* caller,
    int line);

#endif
