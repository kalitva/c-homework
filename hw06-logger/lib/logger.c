#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "log_helper.h"

struct logger {
  FILE* file;
  log_level level;
  int error_code;
};

const char* const levels[] = {
  [TRACE] = "TRACE",
  [DEBUG] = "DEBUG",
  [INFO] = "INFO",
  [WARN] = "WARN",
  [ERROR] = "ERROR",
};

logger* log_init(char* filename, log_level level)
{
  logger* logger = malloc(sizeof(struct logger));
  logger->file = fopen(filename, "a+");
  logger->level = level;
  logger->error_code = 0;

  if (!logger->file) {
    logger->error_code = FILE_NOT_FOUND_ERROR;
    return NULL;
  }

  return logger;
}

static int log_internal(logger* logger, log_level level, char* message);

void log_set_level(logger* logger, log_level level)
{
  logger->level = level;
}

int log_trace(logger* logger, char *message)
{
  return log_internal(logger, TRACE, message);
}

int log_debug(logger* logger, char *message)
{
  return log_internal(logger, DEBUG, message);
}

int log_info(logger* logger, char *message)
{
  return log_internal(logger, INFO, message);
}

int log_warn(logger* logger, char *message)
{
  return log_internal(logger, WARN, message);
}

int log_error(logger* logger, char *message)
{
  return log_internal(logger, ERROR, message);
}

void log_clean(logger* logger)
{
  fclose(logger->file);
  free(logger);
}

static int log_internal(logger* logger, log_level level, char* message)
{
  if (level < logger->level) {
    return 0;
  }

  char* date_time = current_date_time();
  int bytes = fprintf(logger->file, "%s [%s] %s\n", date_time, levels[level], message);
  free(date_time);
  if (!bytes) {
    logger->error_code = WRITE_FILE_ERROR;
  }

  return logger->error_code;
}
