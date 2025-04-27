#ifndef CONFIG_H
#define CONFIG_H

#define PARAM_VALUE_SEPARATOR '='
#define CONFIG_MAX_LINE 255

int init_config(const char* path);
int get_file(char* path);
void destroy_config();

#endif
