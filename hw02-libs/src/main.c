#include <stdio.h>
#include <stdlib.h>

#include "weather.h"
#include "weather_client.h"
#include "weather_view.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("city is required\n");
    return 1;
  }

  char* city = argv[1];
  weather* w = get_weather(city);

  if (w == NULL) {
    fprintf(stderr, "request failed\n");
    return 1;
  }

  if (w->has_error == true) {
    fprintf(stderr, "%s\n", w->error_message);
    free(w);
    return 1;
  }

  print_weather(w);
  weather_free(w);

  return 0;
}
