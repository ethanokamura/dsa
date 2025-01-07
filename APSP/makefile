CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -g

p9: main.o find_paths.o
	$(CPP) $(CPPFLAGS) main.o find_paths.o -o p9

main.o: main.cpp find_paths.h
	$(CPP) $(CPPFLAGS) -c main.cpp

find_paths.o: find_paths.cpp find_paths.h
	$(CPP) $(CPPFLAGS) -c find_paths.cpp

clean:
	rm -f p9 *.o *~ *.txt *.out
