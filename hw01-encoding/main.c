#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "encoding.h"

int main(int argc, char** argv)
{
  if (argc != 3) {
    printf("usage: 'encoding <encoding name> <filename>'\n");
    return 1;
  }

  const char* encoding_name = argv[1];
	enum encoding encoding = encoding_from_string(encoding_name);
  if (encoding == UNDEFINED_ENCODING) {
    printf("encoding '%s' is not supported\n", encoding_name);
    return 1;
  }

  const char* filename = argv[2];
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("can not open file '%s' \n", filename);
    return 1;
  }

  char* text = convert(file, encoding);
  printf("%s\n", text);
  free(text);

  return 0;
}
