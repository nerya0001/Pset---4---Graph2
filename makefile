CC=gcc
FLAGS=-Wall -g

all: graph

libgraphAlgo.a: graphAlgo.o nodes.o edges.o
	$(AR) -rcs libgraphAlgo.a graphAlgo.o nodes.o edges.o

nodes.o: nodes.c graphAlgo.h
	$(CC) $(FLAGS) -c nodes.c
edges.o: edges.c graphAlgo.h
	$(CC) $(FLAGS) -c edges.c
graphAlgo.o: graphAlgo.c graphAlgo.h
	$(CC) $(FLAGS) -c graphAlgo.c
main.o: main.c graphAlgo.h
	$(CC) $(FLAGS) -c main.c

graph: main.o libgraphAlgo.a
	$(CC) $(FLAGS) -o graph main.o libgraphAlgo.a


.PHONY: clean all

clean:
	rm -f *.o *.a graph
