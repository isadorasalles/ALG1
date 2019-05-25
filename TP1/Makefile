
CC = gcc
CFLAGS = -Wall -std=c99

all: build clean

build: main.o candidato.o universidades.o
	$(CC) $(CFLAGS) main.o candidato.o universidades.o -o tp1

main.o:
	$(CC) $(CFLAGS) -c main.c -o main.o

candidato.o:
	$(CC) $(CFLAGS) -c candidato.c -o candidato.o

universidades.o:
	$(CC) $(CFLAGS) -c universidades.c -o universidades.o

clean:
	rm *.o
