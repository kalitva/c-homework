#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "error_codes.h"

static void parse(const char* path, struct config* config);
static void add_to_config(char* param, char* value, struct config* config);

int create_config(const char* path, struct config* config)
{
  if (access(path, F_OK) != 0) {
    return CONFIG_NOT_FOUND_ERROR;
  }
  config->demonized = false;
  config->filepath = NULL;
  config->logfile = NULL;
  config->homedir = NULL;

  parse(path, config);

  if (!config->filepath) {
    return FILEPATH_PARAM_NOT_FOUND_ERROR;
  }

  return 0;
}

void destroy_config(struct config* config)
{
  if (config->filepath) {
    free(config->filepath);
  }
  if (config->logfile) {
    free(config->logfile);
  }
  if (config->homedir) {
    free(config->homedir);
  }
}

static void parse(const char* path, struct config* config)
{
  FILE* file = fopen(path, "r");

  char* line = NULL;
  size_t length = 0;
  while ((getline(&line, &length, file)) != EOF) {
    int i = 0;
    while (line[i] != '\n') {
      if (line[i++] == PARAM_VALUE_SEPARATOR) {
        char param[CONFIG_MAX_LINE];
        strncpy(param, line, i - 1);
        param[i - 1] = 0;

        char value[CONFIG_MAX_LINE];
        strncpy(value, line + i, strlen(line) - i - 1);
        value[strlen(line) - i - 1] = 0;

        add_to_config(param, value, config);
      }
    }
  }

  if (line) {
    free(line);
  }
  fclose(file);
}

static void add_to_config(char* param, char* value, struct config* config)
{
  if (strcmp("filepath", param) == 0) {
    config->filepath = malloc(strlen(value));
    strcpy(config->filepath, value);
  } else if (strcmp("daemonized", param) == 0) {
    config->demonized = strcmp(value, "true") == 0 ? true : false;
  } else if (strcmp("logfile", param) == 0) {
    config->logfile = malloc(strlen(value));
    strcpy(config->logfile, value);
  } else if (strcmp("homedir", param) == 0) {
    config->homedir = malloc(strlen(value));
    strcpy(config->homedir, value);
  }
}
