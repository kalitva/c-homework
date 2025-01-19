#include <stdio.h>
#include "zip_util.h"

int main(int argc, char** argv)
{
  if (argc == 1) {
    printf("file required\n");
    return 1;
  }
  if (argc > 2) {
    printf("files ignored except the first one\n");
  }

  char* filename = argv[1];
  FILE* file = fopen(filename, "rb");

  if (!file) {
    printf("file %s does not exist\n", filename);
    return 1;
  }

  if (is_zipfile(file)) {
    printf("this is a zip archive\n");
    printf("files:\n\n %s\n", list_zipfiles(file));
  } else {
    printf("the file is not a zip archive\n");
  }

  fclose(file);

  return 0;
}
