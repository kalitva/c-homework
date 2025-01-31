CURL_LIB=-L /usr/lib/x86_64-linux-gnu/ -lcurl
JSON_LIB=-L /usr/lib/x86_64-linux-gnu/ -ljson-c

weather: main.c weather_client.c weather_view.c
	$(CC) -o weather main.c weather_client.c weather_view.c \
       	$(CURL_LIB) $(JSON_LIB) \
	-Wall -Wextra -Wpedantic -std=c11 -I.
