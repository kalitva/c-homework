#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define LOG_MESSAGE_FORMAT "%s [%s] '%s' in %s line:%d\n"

#define FILE_NOT_FOUND_ERROR 1
#define MEMORY_ALLOCATION_ERROR 3

typedef enum {
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
} log_level;

typedef struct logger logger;

logger* log_init(const char* filename, log_level level);
void log_clean(logger* logger);

#define log_trace(logger, message) \
  (_log_internal(logger, TRACE, message, __func__, __LINE__))
#define log_debug(logger, message) \
  (_log_internal(logger, DEBUG, message, __func__, __LINE__))
#define log_info(logger, message) \
  (_log_internal(logger, INFO, message, __func__, __LINE__))
#define log_warn(logger, message) \
  (_log_internal(logger, WARN, message, __func__, __LINE__))
#define log_error(logger, message) \
  (_log_internal(logger, ERROR, message, __func__, __LINE__))

void _log_internal(logger* logger,
    log_level level,
    char* message,
    const char* caller,
    int line);

#endif
