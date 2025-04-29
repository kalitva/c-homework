#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

#include "config.h"
#include "error_codes.h"

static FILE* config = NULL;
static char* filepath = NULL;

static int find_value(const char* param_name, char* value);

int init_config(const char* config_path)
{
  config = fopen(config_path, "r");
  if (!config) {
    return CONFIG_NOT_FOUND_ERROR;
  }

  return 0;
}

int get_filepath(char* filepath_dest)
{
  if (filepath) {
    strcpy(filepath_dest, filepath);
    return 0;
  }

  int code = find_value("filepath", filepath_dest);
  if (code == 0) {
    filepath = malloc(CONFIG_MAX_LINE);
    strcpy(filepath, filepath_dest);
  }

  return code;
}

void destroy_config()
{
  fclose(config);
  if (filepath) {
    free(filepath);
  }
}

static int find_value(const char* param_name, char* param_value)
{
  fseek(config, 0, SEEK_SET);
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

        free(line);
        return 0;
      }
    }
  }

  return PARAM_NOT_FOUND_ERROR;
}
