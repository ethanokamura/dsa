CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -g

p7: main.o binary_search_tree.o
	$(CPP) $(CPPFLAGS) main.o binary_search_tree.o -o p7

main.o: main.cpp binary_search_tree.h
	$(CPP) $(CPPFLAGS) -c main.cpp

binary_search_tree.o: binary_search_tree.cpp binary_search_tree.h
	$(CPP) $(CPPFLAGS) -c binary_search_tree.cpp

clean:
	rm -f p7 *.o *~ *.txt *.out
