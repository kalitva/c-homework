#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

#define PARAM_VALUE_SEPARATOR '='
#define CONFIG_MAX_LINE 255

struct config {
  char* filepath;
  bool demonized;
};

int create_config(const char* path, struct config*);
int get_filepath(char* filepath_dest);
void destroy_config(struct config*);

#endif
