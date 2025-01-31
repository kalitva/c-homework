#ifndef WEATHER_H
#define WEATHER_H

typedef struct {
  const char* temperature;
  const char* max_temperature;
  const char* min_temperature;
  const char* date;
} day_forecast;

typedef struct {
  const char* temperature;
  const char* cloudcover;
  const char* humidity;
  const char* pressure;
  const char* visibility;
} current_contiditions;

typedef struct {
  current_contiditions conditions;
  day_forecast* forecast;
  int days;
} weather;

#endif
