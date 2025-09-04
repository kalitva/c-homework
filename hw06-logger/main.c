#include <unistd.h>

#include "src/logger.h"

void nested_func_1(logger* logger) {
  log_error(logger, "error message");
}

void nested_func_2(logger* logger) {
  nested_func_1(logger);
}

void log_func(logger* logger) {
  log_debug(logger, "debug from log_func");
}

int main() {
  logger* logger = log_init("logfile.log", DEBUG);

  log_func(logger);

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
