CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -g -std=c17

FindComponents: FindComponents.o Graph.o List.o
	$(CC) $(CCFLAGS) FindComponents.o Graph.o List.o -o FindComponents

# GraphTest: GraphTest.o Graph.o List.o
# 	$(CC) $(CCFLAGS) GraphTest.o Graph.o List.o -o GraphTest

FindComponents.o: FindComponents.c Graph.h
	$(CC) $(CCFLAGS) -c FindComponents.c

Graph.o: Graph.c Graph.h List.h
	$(CC) $(CCFLAGS) -c Graph.c

List.o: List.c List.h
	$(CC) $(CCFLAGS) -c List.c

clean:
	rm -f FindComponents GraphTest *.o *~ *.txt *.out ModelGraphTest ModelListTest
