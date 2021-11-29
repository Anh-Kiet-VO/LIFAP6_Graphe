CC = g++
CFLAGS = -Wall -ggdb

all: bin/main


bin/main: obj/main.o obj/graphe.o
	$(CC) $(CFLAGS) obj/main.o obj/graphe.o -o bin/main

obj/main.o: src/main.cpp src/graphe.h
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/graphe.o: src/graphe.cpp src/graphe.h
	$(CC) $(CFLAGS) -c src/graphe.cpp -o obj/graphe.o

clean:
	rm obj/*.o

veryclean: clean
	rm obj/*.o

