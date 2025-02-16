#include <pthread.h>
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

static pthread_mutex_t mutex;

void log_set_level(logger* logger, log_level level)
{
  logger->level = level;
}

void log_clean(logger* logger)
{
  fclose(logger->file);
  free(logger);
}

int _log_internal(logger* logger, log_level level, char* message, const char* caller, int line)
{
  if (level < logger->level) {
    return 0;
  }

  char* date_time = current_date_time();

  pthread_mutex_lock(&mutex);
  int bytes = fprintf(logger->file, "%s [%s] %s %s line:%d\n",
      date_time, levels[level], message, caller, line);
  pthread_mutex_unlock (&mutex);

  if (!bytes) {
    logger->error_code = WRITE_FILE_ERROR;
  }

  free(date_time);

  return logger->error_code;
}
