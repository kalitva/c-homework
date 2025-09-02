#include <unistd.h>

#include "lib/logapi.h"

void nested_func_1(logger* logger)
{
  log_error(logger, "error message");
}

void nested_func_2(logger* logger)
{
  nested_func_1(logger);
}

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

  nested_func_2(logger);

  log_clean(logger);
}
