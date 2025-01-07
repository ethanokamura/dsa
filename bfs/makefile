CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -Wunused

p8: main.o pathfinder.o
	$(CPP) $(CPPFLAGS) main.o pathfinder.o -o p8

main.o: main.cpp pathfinder.h
	$(CPP) $(CPPFLAGS) -c main.cpp

pathfind.o: pathfinder.cpp pathfinder.h queue.h linked_list.h
	$(CPP) $(CPPFLAGS) -c pathfinder.cpp

clean:
	rm -f p8 *.o *~ *.txt *.out
