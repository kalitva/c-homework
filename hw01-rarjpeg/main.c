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

  zip_summary summary = read_zip(file);
  if (summary.is_zip) {
  //  printf("this is a zip archive\n");
  //  printf("files:\n\n %s\n", summary.filenames);
  } else {
    printf("the file is not a zip archive\n");
  }

  fclose(file);

  return 0;
}
