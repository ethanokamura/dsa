CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic

queue: main.o
	$(CPP) $(CPPFLAGS) main.o -o queue

main.o: main.cpp queue.h linked_list.h
	$(CPP) $(CPPFLAGS) -c main.cpp

clean:
	rm -f queue *.o *~
