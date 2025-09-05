#ifndef WEATHER_CLIENT_H
#define WEATHER_CLIENT_H

#include <stddef.h>
#include "weather.h"

typedef struct {
  char* buf;
  size_t size;
} memory;

weather* get_weather(const char* city);
void weather_free(weather* weather);

#endif
