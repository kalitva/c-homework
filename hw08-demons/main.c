#include <stdio.h>
#include <linux/limits.h>

#include "src/config.h"
#include "src/error_codes.h"

int main(int argc, char** argv)
{
  init_config(argv[1]);
  char path[PATH_MAX];


  int code = get_file(path);
  if (code == 0) {
    printf("%s\n", path);
  } else if (code == PARAM_NOT_FOUND_ERROR) {
    printf("parameter 'file' not found\n");
  }

  destroy_config();
}
