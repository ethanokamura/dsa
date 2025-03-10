CPP = g++
CPPFLAGS = -Wall -Wextra -pedantic -g

hashtable: main.o hashtable.o record.o
	$(CPP) $(CPPFLAGS) main.o hashtable.o record.o -o hashtable

main.o: main.cpp hashtable.h
	$(CPP) $(CPPFLAGS) -c main.cpp

hashtable.o: hashtable.cpp hashtable.h linked_list.h record.h
	$(CPP) $(CPPFLAGS) -c hashtable.cpp

record.o: record.cpp record.h
	$(CPP) $(CPPFLAGS) -c record.cpp

clean:
	rm -f hashtable *.o *~ *.txt *.out
