#ifndef CONFIG_H
#define CONFIG_H

#define PARAM_VALUE_SEPARATOR '='
#define CONFIG_MAX_LINE 255

int init_config(const char* config_path);
int get_filepath(char* filepath_dest);
void destroy_config();

#endif
