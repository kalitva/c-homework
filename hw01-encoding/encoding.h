#ifndef ENCODING_H
#define ENCODING_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define ANSII_SET_SIZE 127

enum encoding {
  CP_1251,
  KOI8_R,
  ISO_8859_5,
  UNDEFINED_ENCODING = INT_MAX,
};

char* convert(FILE* file, enum encoding encoding);
enum encoding encoding_from_string(const char* encoding);

#endif
