#include <stdio.h>
#include <linux/limits.h>

#include "src/config.h"
#include "src/error_codes.h"
#include "src/file_size_socket.h"

int main(int argc, char** argv)
{
  char* config_path = argv[1];
  int code = init_config(config_path);
  if (code == CONFIG_NOT_FOUND_ERROR) {
    printf("config file '%s' not found\n", config_path);
    return CONFIG_NOT_FOUND_ERROR;
  }

  code = listen_file();
  destroy_config();

  if (code == STREAM_BINDING_ERROR) {
    printf("stream binding error\n");
    return STREAM_BINDING_ERROR;
  } else if (code == OPEN_SOCKET_ERROR) {
    printf("open socket error\n");
    return OPEN_SOCKET_ERROR;
  } else if (code == PARAM_NOT_FOUND_ERROR) {
    printf("parameter not found\n");
    return PARAM_NOT_FOUND_ERROR;
  } else if (code == FILE_NOT_FOUND_ERROR) {
    printf("file not found\n");
    return FILE_NOT_FOUND_ERROR;
  }

  return 0;
}
