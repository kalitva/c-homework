#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "encoding.h"

int main(int argc, char** argv)
{
  if (argc != 3) {
    printf("usage: 'encoding <filename> <encoding type>'\n");
    return 1;
  }

  char* filename = argv[1];
  if (access(filename, R_OK) != 0) {
    printf("can not open file '%s' \n", filename);
    return 1;
  }

  const char* encoding = argv[2];
  if (!is_encoding_supported(encoding)) {
    printf("encoding '%s' is not supported\n", encoding);
    return 1;
  }

  char* text = convert(filename, encoding);
  printf("%s\n", text);
  free(text);

  return 0;
}
