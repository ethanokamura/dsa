CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -g

p3: main.o
	$(CPP) $(CPPFLAGS) main.o -o p3

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp

clean:
	rm -f p3 *.o *~ *.txt *.out
