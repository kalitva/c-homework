#ifndef WEATHER_H
#define WEATHER_H

#include <stdbool.h>

typedef struct {
  char* temperature;
  char* max_temperature;
  char* min_temperature;
  char* date;
} day_forecast;

typedef struct {
  char* temperature;
  char* cloudcover;
  char* humidity;
  char* pressure;
  char* visibility;
} current_contiditions;

typedef struct {
  current_contiditions conditions;
  day_forecast* forecast;
  int days;
  bool has_error;
  char error_message[100];
} weather;

#endif
