CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11

all: main.c message.c logger.c
	$(CC) $(CFLAGS) main.c message.c logger.c -o main

clean:
	rm main