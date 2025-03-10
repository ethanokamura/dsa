CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic

stack: main.o
	$(CPP) $(CPPFLAGS) main.o -o stack

main.o: main.cpp stack.h linked_list.h
	$(CPP) $(CPPFLAGS) -c main.cpp

clean:
	rm -f stack *.o *~
