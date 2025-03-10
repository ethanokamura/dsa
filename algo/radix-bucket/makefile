CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -g

p4: main.o
	$(CPP) $(CPPFLAGS) main.o -o p4

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp

clean:
	rm -f p4 *.o *~ *.txt *.out
