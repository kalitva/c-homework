#ifndef LOGAPI_H
#define LOGAPI_H

#define FILE_NOT_FOUND_ERROR 1
#define MEMORY_ALLOCATION_ERROR 2

typedef struct logger logger;

typedef enum {
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
} log_level;

logger* log_init(char* filename, log_level level);
void log_clean(logger* logger);

void log_trace(logger* logger, const char* message);
void log_debug(logger* logger, const char* message);
void log_info(logger* logger, const char* message);
void log_warn(logger* logger, const char* message);
void log_error(logger* logger, const char* message);

#endif
