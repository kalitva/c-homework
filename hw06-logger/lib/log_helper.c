#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "log_helper.h"

char* current_date_time()
{
  char date_time[20];
  time_t now = time(0);
  strftime(date_time, 100, DATE_TIME_FORMAT, localtime(&now));

  struct timeval time;
  gettimeofday(&time, NULL);
  long milliseconds = (time.tv_usec / 1000);

  char* date_time_with_milliseconds = malloc(DATE_TIME_LENGTH);
  sprintf(date_time_with_milliseconds, "%s.%ld", date_time, milliseconds);

  return date_time_with_milliseconds;
}
