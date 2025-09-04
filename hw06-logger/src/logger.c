#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_helper.h"
#include "logger.h"

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

logger* log_init(const char* filename, log_level level) {
  logger* logger = malloc(sizeof(struct logger));
  if (!logger) {
    return NULL;
  }
  logger->file = fopen(filename, "a+");
  logger->level = level;
  logger->error_code = 0;

  if (!logger->file) {
    logger->error_code = FILE_NOT_FOUND_ERROR;
  }

  return logger;
}

void log_clean(logger* logger) {
  fclose(logger->file);
  free(logger);
}

static pthread_mutex_t mutex;

void _log_internal(logger* logger,
    log_level level,
    char* message,
    const char* caller,
    int line) {
  if (level < logger->level) {
    return;
  }

  char* date_time = current_date_time();
  if (!date_time) {
    logger->error_code = MEMORY_ALLOCATION_ERROR;
    return;
  }

  pthread_mutex_lock(&mutex);

  fprintf(logger->file, LOG_MESSAGE_FORMAT,
      date_time, levels[level], message, caller, line);
  free(date_time);

  if (level == ERROR) {
    char* stack_trace = get_stack_trace();
    if (stack_trace) {
      fprintf(logger->file, "%s\n", stack_trace);
      free(stack_trace);
    } else {
      logger->error_code = MEMORY_ALLOCATION_ERROR;
    }
  }

  pthread_mutex_unlock(&mutex);
}
