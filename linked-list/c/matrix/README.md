# Programming Assignment 4:

This program implements an nxn Matrix. With these strutures, we perform basic Matrix manipulation procedures.

## How it works:
1. Assembles the Matrix ADTs.
2. Runs Elementary Operations on Matrices.
3. Outputs the Calculations.

## Directory:

```
pa4/
  ├── Sparse.c      # containing the primary logic for the program
  ├── Matrix.c      # implements the Matrix ADT and inner structures
  ├── Matrix.h      # defines the Matrix structure and related methods
  ├── MatrixTest.c  # tests the provided functions required to implement the Matrix ADT
  ├── List.c        # implements the doubly linked list and inner nodes
  ├── List.h        # defines the doubly linked list
  ├── ListTest.h    # tests the provided functions required to implement the List ADT
  ├── Makefile      # creates and links the above files to compile to a single executable
  └── README.md     # description of the program and given directory
```

## Tests:
For `MatrixTest.c`, I ran a series of tests that covered all of the defined methods within `Matrix.c`. I created a bash script to run a series of inputs and compared to the expected outputs to ensure the results were as expected.

```sh
#!/bin/bash

for i in "$@"; do  # Loop over all arguments passed to the script
  # Define file paths
  INPUT_FILE="in$i.txt"
  EXPECTED_OUTPUT="data/out$i.txt"
  ACTUAL_OUTPUT="data/out.txt"

  # Run Sparse and save the output to out.txt
  echo "Running data/$INPUT_FILE"
  # Uncomment for debugging:
  make MatrixTest
  valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./MatrixTest "data/$INPUT_FILE" "$ACTUAL_OUTPUT"

  # Compare output with expected output using diff -Z
  if [ -f "$EXPECTED_OUTPUT" ]; then
    echo "Comparing output of $ACTUAL_OUTPUT with $EXPECTED_OUTPUT"
    diff -Z "$ACTUAL_OUTPUT" "$EXPECTED_OUTPUT"

    if [ $? -eq 0 ]; then
      echo "✅ Test passed: Output matches expected output!"
    else
      echo "❌ Test failed: Differences found."
    fi
  else
    echo "⚠️ Warning: Expected output file '$EXPECTED_OUTPUT' not found!"
  fi
  make clean
done
```

## Compilation:

The make file compiles the code with the following flags to ensure consistency:
```
gcc -Wall -Wextra -pedantic -g -std=c17
```
