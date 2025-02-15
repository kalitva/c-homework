#include <unistd.h>

#include "lib/logger.h"

int main()
{
  logger* logger = log_init("logfile.log", DEBUG);

  log_trace(logger, "shoud not be logged");
  usleep(1000);
  log_debug(logger, "debug message");
  usleep(1000);
  log_info(logger, "info message");
  usleep(10000);
  log_warn(logger, "warn message");

  log_clean(logger);
}
