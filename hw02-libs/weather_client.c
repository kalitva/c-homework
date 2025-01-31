#include <curl/curl.h>
#include <json-c/json_object.h>
#include <json-c/json_types.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#include "weather_client.h"
#include "weather.h"

static size_t write_response(void* response, size_t size, size_t nmemb, memory* mem);
static weather* response_to_weather(memory* mem);

weather* get_weather(char* city)
{
  memory mem;
  mem.buf= malloc(1);
  mem.size = 0;

  char url[50];
  sprintf(url, "http://wttr.in/%s?format=j1", city);

  CURL* curl_handle;
  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_response);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &mem);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  CURLcode res = curl_easy_perform(curl_handle);
  if (res != CURLE_OK) {
    fprintf(stderr, "request failed: %s\n", mem.buf);
  }

  printf("%lu bytes retrieved\n", mem.size);

  weather* w = response_to_weather(&mem);

  curl_easy_cleanup(curl_handle);
  free(mem.buf);
  curl_global_cleanup();

  return w;
}

void weather_free(weather *weather)
{
  free(weather->forecast);
  free(weather);
}

static weather* response_to_weather(memory* mem)
{
  weather* w = malloc(sizeof(weather));
  json_object* root = json_tokener_parse(mem->buf);
  json_object* cc = json_object_array_get_idx(json_object_object_get(root, "current_condition"), 0);
  w->conditions.cloudcover = json_object_get_string(json_object_object_get(cc, "cloudcover"));
  w->conditions.temperature = json_object_get_string(json_object_object_get(cc, "temp_C"));
  w->conditions.humidity= json_object_get_string(json_object_object_get(cc, "humidity"));
  w->conditions.pressure= json_object_get_string(json_object_object_get(cc, "pressure"));
  w->conditions.visibility = json_object_get_string(json_object_object_get(cc, "visibility"));

  json_object* days = json_object_object_get(root, "weather");
  w->days = json_object_array_length(days);
  w->forecast = malloc(w->days * sizeof(day_forecast));

  for (int i = 0; i < w->days ; i++) {
    json_object* day = json_object_array_get_idx(days, i);
    day_forecast* df = &(w->forecast[i]);
    df->date = json_object_get_string(json_object_object_get(day, "date"));
    df->min_temperature = json_object_get_string(json_object_object_get(day, "mintempC"));
    df->max_temperature = json_object_get_string(json_object_object_get(day, "maxtempC"));
    df->temperature = json_object_get_string(json_object_object_get(day, "avgtempC"));
  }

  json_object_put(root);

  return w;
}

static size_t write_response(void* response, size_t size, size_t nmemb, memory* mem)
{
  size_t realsize = size * nmemb;
  mem->buf = realloc(mem->buf, mem->size + realsize + 1);

  if (!mem->buf) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->buf[mem->size]), response, realsize);
  mem->size += realsize;
  mem->buf[mem->size] = 0;

  return realsize;
}
