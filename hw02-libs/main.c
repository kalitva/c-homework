#include <stdio.h>

#include "weather.h"
#include "weather_client.h"
#include "weather_view.h"


int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("a city required\n");
    return 1;
  }

  char* city = argv[1];
  weather* w = get_weather(city);
  print_weather(w);
  weather_free(w);
}
