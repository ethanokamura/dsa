This program implements breadth first search using an adjacency list constructed from a Linked List

## How it works:

  1. Using command line arguments, the program inside `FindPath.c` reads an input and output file provided by the user.
  2. After reading the input file, the program runs breadth first search algorithm to find the shortest path for given verticies.
  3. Once the algorithm is complete, the program writes the newly sorted data into the output file.

## Directory:

```
bfs/c/
  ├── FindPath.c   # containing the primary logic for the program
  ├── Graph.c      # implements the graph ADT and inner structures
  ├── Graph.h      # defines the graph structure
  ├── GraphTest.c  # tests the provided functions required to implement the graph
  ├── List.c       # implements the doubly linked list and inner nodes
  ├── List.h       # defines the doubly linked list
  ├── Makefile     # creates and links the above files to compile to a single executable
  └── README.md    # description of the program and given directory
```

## Tests:

This program runs against the local and self created test cases. When used with valgrind, no memory leaks occurred. My tests consisted of monitoring the behaviour of the ListObj when manipulating or navigating the list. I made sure to cover all the functions implemented in `Graph.h`.

## Compilation:

The make file compiles the code with the following flags to ensure consistency:
```
gcc -Wall -Wextra -pedantic -g -std=c17
```
