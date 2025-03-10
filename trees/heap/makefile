CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -g

p2: main.o minimum_heap.o
	$(CPP) $(CPPFLAGS) main.o minimum_heap.o -o p2

main.o: main.cpp minimum_heap.h
	$(CPP) $(CPPFLAGS) -c main.cpp

minimum_heap.o: minimum_heap.cpp minimum_heap.h
	$(CPP) $(CPPFLAGS) -c minimum_heap.cpp

clean:
	rm -f p2 *.o *~ *.txt *.out
