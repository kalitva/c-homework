CFLAGS+= -Wall -Wextra -Wpedantic -std=c11 -I.
DEPS=zip_util.h

rarjpeg: main.c zip_util.c
	$(CC) -o rarjpeg main.c zip_util.c $(CFLAGS)
