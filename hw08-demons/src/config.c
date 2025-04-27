#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

#include "config.h"
#include "error_codes.h"

static FILE* config = NULL;

static int find_value(const char* param_name, char* value);

int init_config(const char* path)
{
  config = fopen(path, "r");
  if (!config) {
    return CONFIG_NOT_FOUND_ERROR;
  }

  return 0;
}

int get_file(char* path)
{
  return find_value("file", path);
}

void destroy_config()
{
  fclose(config);
}

static int find_value(const char* param_name, char* param_value)
{
  char* line = NULL;
  size_t length = 0;

  while ((getline(&line, &length, config)) != EOF) {
    int i = 0;
    while (line[i] != '\n') {
      if (line[i++] == PARAM_VALUE_SEPARATOR) {
        char param[CONFIG_MAX_LINE];
        strncpy(param, line, i - 1);
        param[i - 1] = 0;

        if (strcmp(param_name, param) != 0) {
          continue;
        }

        char value[CONFIG_MAX_LINE];
        strncpy(value, line + i, strlen(line) - i - 1);
        value[strlen(line) - i - 1] = 0;
        strcpy(param_value, value);

        return 0;
      }
    }
  }

  if (line) {
    free(line);
  }

  return PARAM_NOT_FOUND_ERROR;
}
