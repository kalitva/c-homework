#include "weather_client.h"
#include <stdio.h>


int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("a city required\n");
    return 1;
  }

  get_weather(argv[1]);
}
