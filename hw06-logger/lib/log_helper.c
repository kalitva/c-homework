#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "log_helper.h"

char* current_date_time() {
  char date_time[20];
  time_t now = time(0);
  strftime(date_time, 100, DATE_TIME_FORMAT, localtime(&now));

  struct timeval time;
  gettimeofday(&time, NULL);
  int milliseconds = (time.tv_usec / 1000);

  char* date_time_with_milliseconds = malloc(DATE_TIME_LENGTH);
  if (!date_time_with_milliseconds) {
    return NULL;
  }
  sprintf(date_time_with_milliseconds, "%s.%d", date_time, milliseconds);

  return date_time_with_milliseconds;
}

char* get_stack_trace() {
  void* buffer[100];
  int size = backtrace(buffer, 100);
  char** strings = backtrace_symbols(buffer, size);

  if (strings == NULL) {
    return NULL;
  }

  int total_size = 0;
  for (int i = 0; i < size; i++) {
    total_size += (strlen(strings[i]) + 1);
  }

  char* backtrace = malloc(total_size + 1);
  if (!backtrace) {
    return NULL;
  }
  backtrace[0] = '\0';

  for (int i = 0; i < size; i++) {
    int line_size = strlen(strings[i]) + 4;
    char* line = malloc(line_size);
    if (!line) {
      return NULL;
    }
    sprintf(line, "  %s\n", strings[i]);
    strcat(backtrace, line);
  }
  free(strings);

  return backtrace;
}
