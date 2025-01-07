CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -g

p6: main.o maze_generation.o disjoint_set.o
	$(CPP) $(CPPFLAGS) main.o maze_generation.o disjoint_set.o -o p6

main.o: main.cpp maze_generation.h
	$(CPP) $(CPPFLAGS) -c main.cpp

maze_generation.o: maze_generation.cpp maze_generation.h disjoint_set.h
	$(CPP) $(CPPFLAGS) -c maze_generation.cpp

disjoint_set.o: disjoint_set.cpp disjoint_set.h
	$(CPP) $(CPPFLAGS) -c disjoint_set.cpp

clean:
	rm -f p6 *.o *~ *.txt *.out
