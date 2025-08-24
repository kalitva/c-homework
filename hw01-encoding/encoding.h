#ifndef ENCODING_H
#define ENCODING_H

#include <stdbool.h>

#define ANSII_SET_SIZE 127

enum encoding {
  CP_1251,
  KOI8_R,
  ISO_8859_5,
};

bool is_encoding_supported(const char* encoding);
char* convert(const char* filename, const char* encoding);

#endif
