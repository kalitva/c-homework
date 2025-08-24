CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c11 -I.
DEPS=encoding.h charsets.h

rarjpeg: main.c encoding.c charsets.c
	$(CC) -o encoding main.c encoding.c charsets.c $(CFLAGS)
