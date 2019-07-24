
CC = gcc 
CFLAGS = -Wall -std=c99  

all: build clean

build: main.o graph.o tarefa1.o tarefa2.o
	$(CC) $(CFLAGS) main.o graph.o tarefa1.o tarefa2.o -o tp3 

main.o:
	$(CC) $(CFLAGS) -c main.c -o main.o

candidato.o:
	$(CC) $(CFLAGS) -c graph.c -o graph.o

tarefa1.o:
	$(CC) $(CFLAGS) -c tarefa1.c -o tarefa1.o

tarefa2.o:
	$(CC) $(CFLAGS) -c tarefa2.c -o tarefa2.o

clean:
	rm *.o
