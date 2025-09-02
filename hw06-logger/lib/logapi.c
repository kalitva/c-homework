#include "logapi.h"
#include "log_internal.h"

logger* log_init(char* filename, log_level level) {
  return log_init_internal(filename, level);
}

void log_clean(logger* logger) {
  log_clean_internal(logger);
}

void log_trace(logger* logger, const char* message) {
  LOG(logger, message, TRACE);
}

void log_debug(logger* logger, const char* message) {
  LOG(logger, message, DEBUG);
}

void log_info(logger* logger, const char* message) {
  LOG(logger, message, INFO);
}

void log_warn(logger* logger, const char* message) {
  LOG(logger, message, WARN);
}

void log_error(logger* logger, const char* message) {
  LOG(logger, message, ERROR);
}
