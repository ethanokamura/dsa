#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency and Order
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryTest under valgrind
#------------------------------------------------------------------------------

EXEC1          = WordFrequency
EXEC2          = Order
ADT            = Dictionary
SOURCE1        = $(EXEC1).cpp
OBJECT1        = $(EXEC1).o
SOURCE2        = $(EXEC2).cpp
OBJECT2        = $(EXEC2).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJECT1) $(ADT_OBJECT)
	$(LINK) $(EXEC1) $(OBJECT1) $(ADT_OBJECT)

$(EXEC2): $(OBJECT2) $(ADT_OBJECT)
	$(LINK) $(EXEC2) $(OBJECT2) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT1): $(SOURCE1) $(ADT_HEADER)
	$(COMPILE) $(SOURCE1)

$(OBJECT2): $(SOURCE2) $(ADT_HEADER)
	$(COMPILE) $(SOURCE2)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(EXEC1) $(EXEC2) $(ADT_TEST) $(OBJECT1) $(OBJECT2) $(ADT_TEST).o $(ADT_OBJECT) ModelDictionaryTest *.txt

$(EXEC1)Check: $(EXEC1)
	$(MEMCHECK) $(EXEC1) Gutenberg myGutenberg-out

$(EXEC2)Check: $(EXEC2)
	$(MEMCHECK) $(EXEC2) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
