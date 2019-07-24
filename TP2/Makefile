
CC = gcc 
CFLAGS = -Wall -std=c99  

all: build clean

build: main.o graph.o distance.o
	$(CC) $(CFLAGS) main.o graph.o distance.o -o tp2 -lm

main.o:
	$(CC) $(CFLAGS) -c main.c -o main.o

candidato.o:
	$(CC) $(CFLAGS) -c graph.c -o graph.o

distance.o:
	$(CC) $(CFLAGS) -c distance.c -o distance.o

clean:
	rm *.o
