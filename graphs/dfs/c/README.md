This program finds a Graph ADT's strongly connected components using depth first search and transposition with a series of adjacency lists constructed from an array of doubly Linked Lists.

## How it works:

  1. Using command line arguments, the program inside `FindComponents.c` reads an input and output file provided by the user.
  2. After reading the input file, the program runs builds adjacency lists to define the directed graph's structure.
  3. DFS is performed on the graph to retrieve the topoligically sorted vertices.
  4. The graph is then transposed to inverse the directed edges between vertices.
  5. DFS is performed on the transposed graph to find the strongly connected components.
  6. Following low link values inside DFS's visit helper function, we are able to identify these connections.
  7. Once the algorithm is complete, the program extracts and outputs the SCC to the output file.

## Directory:

```
dfs/c/
  ├── FindComponents.c  # containing the primary logic for the program
  ├── Graph.c           # implements the graph ADT and inner structures
  ├── Graph.h           # defines the graph structure
  ├── GraphTest.c       # tests the provided functions required to implement the graph
  ├── List.c            # implements the doubly linked list and inner nodes
  ├── List.h            # defines the doubly linked list
  ├── Makefile          # creates and links the above files to compile to a single executable
  └── README.md         # description of the program and given directory
```

## Tests:

This program runs against the local and self created test cases. When used with valgrind, no memory leaks occurred. My tests consisted of monitoring the behaviour of the ListObj when manipulating or navigating the list. I made sure to cover all the functions implemented in `Graph.h`.

## Compilation:

The make file compiles the code with the following flags to ensure consistency:
```
gcc -Wall -Wextra -pedantic -g -std=c17
```

## Visit()

To implement the visit function (and the algorithm timer) I chose to use the second approach: "The second approach is to let time be a local variable in DFS(), then pass the address of time to Visit(), making it an input-output variable to Visit()."

I chose this option because it was the perfect mix of simplicity and efficiency.

Here are the reasons I did not pick the other three:
1. Global scope of `visit()` and `time` - I tend to avoid using global scoped variables and functions unless it is crucial. I believe that structures should be strict with which functions are made public. To lean on the safe side, I prefer to start all my methods at the lowest possible scope and then navigate up the tree as needed. This approach avoids any confusion or unnecessary complication. Coming from a C++ background where we use things like `private` and `public`, I tend to only use getters and setters publicly and instead have all of the main functionality and data manipulation privatized.
3. Nested functions are not supported unless using GNU C. For this reason, I chose to avoid using nested functions. I want my program to be able to be used and reused without unnecessary complications.
4. Using a local time clock to `visit()` - local variables (especially in recursive functions) can lead to bloated memory usage.

## Low Link Values

To find the strongly connected components, I decided to implement a system that inspired by Tarjan's Strongly Connected Component Algorithm.

This algorithm uses DFS(G), DFS(G^T) and something called low-link values.

Low link values allowed me find the lowest value linking a cycle. Meaning in a connected loop with vertices of labels 1, 2, and 5, the low link value for all 3 vertices was 1. This allowed me to group together strongly connected components that were defined by their starting vertex within the cycle.

I also chose this method because I had fun researching it!

## Auto Testing:

To modularize my testing, I followed a similar input file to that of the regular inputs for the `FindComponents.c` file.

The input file for testing is as follows:
- 1 line describing the number of vertices.
- a list of integer pairs describing the behaviour of the directed edges

After this, there are 6 more sections. 3 test for the regular Graph ADT and the other 3 test for the transposed Graph ADT.
Each go as follows:
- a list of integer pairs with the expected relationship between a given vertex and parent in the
- a list of integer pairs with the expected relationship between a given vertex and discover time
- a list of integer pairs with the expected relationship between a given vertex and finish time

All sections end with a `0 0` pair.
