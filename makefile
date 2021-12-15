CC = g++
CFLAGS = -Wall -ggdb

all: bin/main

bin/main: obj/main.o obj/astar.o
	$(CC) $(CFLAGS) obj/main.o obj/astar.o -o bin/main

obj/main.o: src/main.cpp src/astar.h
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/astar.o: src/astar.cpp src/astar.h
	$(CC) $(CFLAGS) -c src/astar.cpp -o obj/astar.o

clean:
	rm obj/*.o

veryclean: clean
	rm obj/*.o
