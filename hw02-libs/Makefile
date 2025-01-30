CURL_LIB=-L /usr/lib/x86_64-linux-gnu/ -lcurl

weather: main.c
	$(CC) -o weather main.c $(CURL_LIB) -Wall -Wextra -Wpedantic -std=c11 -I.
