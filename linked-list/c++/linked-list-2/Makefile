#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListTest     make ListTest
#  make clean          removes binary files
#  make check1         runs valgrind on ListTest
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

CC = g++
CCFLAGS = -Wall -Wextra -pedantic -g -std=c++17

Shuffle : Shuffle.o List.o
	$(CC) $(CCFLAGS) -Wall -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
	$(CC) $(CCFLAGS) -Wall -c Shuffle.cpp

ListTest : ListTest.o List.o
	$(CC) $(CCFLAGS) -Wall -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.cpp
	$(CC) $(CCFLAGS) -Wall -c ListTest.cpp

List.o : List.h List.cpp
	$(CC) $(CCFLAGS) -Wall -c List.cpp

clean :
	rm -f Shuffle Shuffle.o ListTest ListTest.o List.o ModelListTest ModelListTest.o *.txt

check1 : ListTest
	valgrind --leak-check=full ListTest

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35