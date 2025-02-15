#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define FILE_NOT_FOUND_ERROR 1;
#define WRITE_FILE_ERROR 2;

typedef enum {
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
} log_level;

typedef struct logger logger;

logger* log_init(char* filename, log_level level);
void log_set_level(logger* logger, log_level level);

int log_trace(logger* logger, char* message);
int log_debug(logger* logger, char* message);
int log_info(logger* logger, char* message);
int log_warn(logger* logger, char* message);
int log_error(logger* logger, char* message);

void log_clean(logger* logger);
#endif
