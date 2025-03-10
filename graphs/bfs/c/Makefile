CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -g -std=c17

FindPath: FindPath.o Graph.o List.o
	$(CC) $(CCFLAGS) FindPath.o Graph.o List.o -o FindPath

# GraphTest: GraphTest.o Graph.o List.o
# 	$(CC) $(CCFLAGS) GraphTest.o Graph.o List.o -o GraphTest

FindPath.o: FindPath.c Graph.h
	$(CC) $(CCFLAGS) -c FindPath.c

Graph.o: Graph.c Graph.h List.h
	$(CC) $(CCFLAGS) -c Graph.c

List.o: List.c List.h
	$(CC) $(CCFLAGS) -c List.c

clean:
	rm -f FindPath GraphTest *.o *~ *.txt *.out
