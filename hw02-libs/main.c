#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char* buf;
  size_t size;
} memory;

static size_t memory_write(void* response, size_t size, size_t nmemb, memory* mem)
{
  size_t realsize = size * nmemb;
  mem->buf = realloc(mem->buf, realsize + 1);

  if (!mem->buf) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(mem->buf, response, realsize);
  mem->buf[realsize] = 0;
  mem->size += realsize;

  return realsize;
}

int main(void)
{
  memory mem;
  mem.buf= malloc(1);
  mem.size = 0;

  CURL* curl_handle;
  curl_global_init(CURL_GLOBAL_ALL);
  curl_handle = curl_easy_init();

  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.example.com/");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, memory_write);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &mem);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  CURLcode res = curl_easy_perform(curl_handle);
  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    return 1;
  }

  printf("%lu bytes retrieved\n", mem.size);
  printf("%s\n", mem.buf);

  curl_easy_cleanup(curl_handle);
  free(mem.buf);
  curl_global_cleanup();

  return 0;
}
