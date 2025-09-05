#include <curl/curl.h>
#include <json-c/json.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "weather.h"
#include "weather_client.h"

static size_t write_response(void* response,
                             size_t size,
                             size_t nmemb,
                             memory* mem);
static weather* response_to_weather(memory* mem);
static char* get_json_string(json_object* json, char* key);

weather* get_weather(const char* city) {
  memory mem = {
      .buf = malloc(1),
      .size = 0,
  };

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
    return NULL;
  }

  weather* w = response_to_weather(&mem);

  curl_easy_cleanup(curl_handle);
  free(mem.buf);
  curl_global_cleanup();

  return w;
}

void weather_free(weather* w) {
  day_forecast* df = w->forecast;
  for (int i = 0; i < w->days; i++) {
    free(df[i].date);
    free(df[i].max_temperature);
    free(df[i].min_temperature);
    free(df[i].temperature);
  }
  free(w->forecast);
  current_contiditions cc = w->conditions;
  free(cc.temperature);
  free(cc.cloudcover);
  free(cc.humidity);
  free(cc.pressure);
  free(cc.visibility);
  free(w);
}

static weather* response_to_weather(memory* mem) {
  weather* w = malloc(sizeof(weather));
  w->has_error = false;
  json_object* root = json_tokener_parse(mem->buf);

  // this usually happens on wrong location
  if (root == NULL) {
    w->has_error = true;
    strcpy(w->error_message, mem->buf);
    return w;
  }

  json_object* cc = json_object_array_get_idx(
      json_object_object_get(root, "current_condition"), 0);
  w->conditions.cloudcover = get_json_string(cc, "cloudcover");
  w->conditions.temperature = get_json_string(cc, "temp_C");
  w->conditions.humidity = get_json_string(cc, "humidity");
  w->conditions.pressure = get_json_string(cc, "pressure");
  w->conditions.visibility = get_json_string(cc, "visibility");

  json_object* days = json_object_object_get(root, "weather");
  w->days = json_object_array_length(days);
  w->forecast = malloc(w->days * sizeof(day_forecast));

  for (int i = 0; i < w->days; i++) {
    json_object* day = json_object_array_get_idx(days, i);
    day_forecast* df = &(w->forecast[i]);
    df->date = get_json_string(day, "date");
    df->min_temperature = get_json_string(day, "mintempC");
    df->max_temperature = get_json_string(day, "maxtempC");
    df->temperature = get_json_string(day, "avgtempC");
  }

  json_object_put(root);

  return w;
}

static char* get_json_string(json_object* json, char* key) {
  const char* src = json_object_get_string(json_object_object_get(json, key));
  char* dest = malloc(strlen(src));
  strcpy(dest, src);

  return dest;
}

static size_t write_response(void* response,
                             size_t size,
                             size_t nmemb,
                             memory* mem) {
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
