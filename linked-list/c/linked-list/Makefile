CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -g -std=c17

Lex: Lex.o List.o
	$(CC) $(CCFLAGS) Lex.o List.o -o Lex

# ListTest: ListTest.o List.o
# 	$(CC) $(CCFLAGS) ListTest.o List.o -o ListTest

Lex.o: Lex.c List.h
	$(CC) $(CCFLAGS) -c Lex.c

ListTest.o: ListTest.c List.h
	$(CC) $(CCFLAGS) -c ListTest.c

List.o: List.c List.h
	$(CC) $(CCFLAGS) -c List.c

clean:
	rm -f Lex ListTest *.o *~ *.txt *.out
