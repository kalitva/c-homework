#include <stdlib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#include "encoding.h"
#include "charsets.h"

const char* const encodings[] = {
  [CP_1251] = "CP-1251",
  [KOI8_R] = "KOI8-R",
  [ISO_8859_5] = "ISO-8859-5",
};

const char** const maps[] = {
  [CP_1251] = cp1251_map,
  [KOI8_R] = koi8_map,
  [ISO_8859_5] = iso_8895_5_map,
};

char* convert(FILE* file, enum encoding encoding)
{
  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  fseek(file, 0, 0);
  char* buf = malloc(file_size * 2);
  const char** map = maps[encoding];

  int c;
  int i = 0;
  while ((c = fgetc(file)) != EOF) {
    if (c <= ANSII_SET_SIZE) {
      buf[i++] = c;
    } else {
      const char* utf_c = map[c];
      buf[i++] = utf_c[0];
      buf[i++] = utf_c[1];
    }
  }

  fclose(file);
  return buf;
}

enum encoding encoding_from_string(const char* encoding)
{
  int length = sizeof(encodings) / sizeof(*encodings);
  for (int i = 0; i < length; i++) {
    if (strcasecmp(encodings[i], encoding) == 0) {
      return i;
    }
  }

  return UNDEFINED_ENCODING;
}
