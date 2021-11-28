CC = g++
CFLAGS = -Wall -ggdb

all: bin/main


bin/main: obj/main.o obj/Graphe.o
	$(CC) $(CFLAGS) obj/main.o obj/Graphe.o -o bin/main

obj/main.o: src/main.cpp src/Graphe.h
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o

obj/Graphe.o: src/Graphe.h src/Graphe.cpp
	$(CC) $(CFLAGS) -c src/Graphe.cpp -o obj/Graphe.o

clean:
	rm obj/*.o

veryclean: clean
	rm obj/*.o

