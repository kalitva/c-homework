#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

#define PARAM_VALUE_SEPARATOR '='
#define CONFIG_MAX_LINE 255

struct config {
  char* filepath;
  bool demonized;
  char* logfile;
  char* homedir;
};

int create_config(const char* path, struct config*);
void destroy_config(struct config*);

#endif
