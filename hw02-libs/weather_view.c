#include "weather_view.h"
#include "weather.h"
#include <stdio.h>

void print_weather(weather* w)
{
  printf("--------- WEATHER CURRENT CONDITIONS -----------\n");
  printf("temperature: %s\n", w->conditions.temperature);
  printf("cloudcover: %s\n", w->conditions.cloudcover);
  printf("humidity: %s\n", w->conditions.humidity);
  printf("pressure: %s\n", w->conditions.pressure);
  printf("visibility: %s\n", w->conditions.visibility);
  printf("\n");

  printf("--------- WEATHER FORECAST -----------\n");
  for (int i = 0; i < w->days; i++) {
    day_forecast* df = &(w->forecast[i]);
    printf("date: %s\n", df->date);
    printf("min temperature: %s\n", df->min_temperature);
    printf("max temperature: %s\n", df->max_temperature);
    printf("temperature: %s\n\n", df->temperature);
  }
}
