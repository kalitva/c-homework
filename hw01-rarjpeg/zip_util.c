#include "zip_util.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

char* list_zipfiles(FILE* file)
{
  return "";
}

bool is_zipfile(FILE* file)
{
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, file_size, SEEK_SET);

  uint32_t sig;
  while (file_size > 0) {
    fread(&sig, sizeof(int32_t), 1, file);
    if (sig == EO_CENTRAL_DIR_SIGNATURE) {
      return true;
    }
    fseek(file, --file_size, SEEK_SET);
  }

  return false;
}
