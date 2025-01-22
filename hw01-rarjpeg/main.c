#include <stdio.h>
#include "zip_util.h"

int main(int argc, char** argv)
{
  if (argc == 1) {
    printf("error: file required\n");
    return 1;
  }
  if (argc > 2) {
    printf("warning: only the first file is processed\n");
  }

  char* filename = argv[1];
  FILE* file = fopen(filename, "rb");

  if (!file) {
    printf("error: file %s does not exist\n", filename);
    return 1;
  }

  if (is_zipfile(file)) {
    printf("this is a zip archive\n");
    print_zip_files(file);
  } else {
    printf("the file is not a zip archive\n");
  }

  fclose(file);

  return 0;
}
