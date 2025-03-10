# Programming Assignment 6:

This program implements a BigInteger data type ensuring correct computations for large numbers.

## How it works:
1. Assembles the `BigInteger` value.
2. Runs basic arithmetic operations on the `BigInteger` objects.
3. Outputs the calculations.

## Directory:

```
pa6/
  ├── Arithmetic.cpp      # containing the primary logic for the program
  ├── BigInteger.cpp      # implements the BigInteger ADT and inner structures
  ├── BigInteger.h        # defines the BigInteger structure and related methods
  ├── BigIntegerTest.cpp  # tests the provided functions required to implement the BigInteger ADT
  ├── List.cpp            # implements the doubly linked list and inner nodes
  ├── List.h              # defines the doubly linked list
  ├── ListTest.h          # tests the provided functions required to implement the List ADT
  ├── Makefile            # creates and links the above files to compile to a single executable
  └── README.md           # description of the program and given directory
```

## Tests:
For `BigIntegerTest.cpp`, I ran a series of tests that covered all of the defined methods within `BigInteger.cpp`. I created a bash script to run a series of inputs and compared to the expected outputs to ensure the results were as expected.

```sh
#!/bin/bash
make

for i in "$@"; do  # Loop over all arguments passed to the script
  # Define file paths
  INPUT_FILE="../data/pa6/in$i.txt"
  EXPECTED_OUTPUT="../data/pa6/out$i.txt"
  ACTUAL_OUTPUT="../data/pa6/out.txt"

  # Run Sparse and save the output to out.txt
  echo "Running data/$INPUT_FILE"

  valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./Arithmetic "$INPUT_FILE" "$ACTUAL_OUTPUT"

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
done

make clean
```

## Compilation:

The make file compiles the code with the following flags to ensure consistency:
```
g++ -Wall -g -std=c++17 -c
```
