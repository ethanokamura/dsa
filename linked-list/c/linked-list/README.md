This program implements a Doubly Linked List.

## How it works:

  1. Using command line arguments, the program inside `Lex.c` reads an input and output file provided by the user.
  2. After reading the input file, the program runs an insertion sort-like algorithm to simultaneously sort and insert values into a List object.
  3. Once the algorithm is complete, the program writes the newly sorted data into the output file.

## Directory:

```
linked-list/
  ├── Lex.c       # containing the primary logic for the program
  ├── List.c      # implements the doubly linked list and inner nodes
  ├── List.h      # defines the doubly linked list
  ├── ListTest.c  # tests the provided functions required to implement the List
  ├── Makefile    # creates and links the above files to compile to a single executable
  └── README.md   # description of the program and given directory
```

## Tests:

This program runs against the local and self created test cases. When used with valgrind, no memory leaks occurred. My tests consisted of monitoring the behaviour of the ListObj when manipulating or navigating the list. I made sure to cover all the functions implemented in `List.h`.

## Compilation:

The make file compiles the code with the following flags to ensure consistency:
```
gcc -Wall -Wextra -pedantic -g -std=c17
```
