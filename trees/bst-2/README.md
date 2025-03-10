# Programming Assignment 7:

This program implements a Dictionary ADT using a Binary Search Tree allowing for fast insertions and lookups.

## How it works:
1. Assembles the `Dictionary` ADT.
2. Inserts keys with their original index as values into the `Dictionary`.
3. Outputs the calculations.

## Directory:

```
pa7/
  ├── Dictionary.cpp      # implements the Dictionary ADT and inner structures
  ├── Dictionary.h        # defines the Dictionary structure and related methods
  ├── DictionaryTest.cpp  # tests the provided functions required to implement the Dictionary ADT
  ├── Makefile            # creates and links the above files to compile to a single executable
  ├── Order.cpp           # containing the primary logic for the program
  └── README.md           # description of the program and given directory
```

## Tests:
For `DictionaryTest.cpp`, I ran a series of tests that covered all of the defined methods within `Dictionary.cpp`. I created a bash script to run a series of inputs and compared to the expected outputs to ensure the results were as expected.

```sh
#!/bin/bash
make DictionaryTest

for i in "$@"; do  # Loop over all arguments passed to the script
  # Define file paths
  INPUT_FILE="../data/pa7/in$i.txt"
  # Run Sparse and save the output to out.txt
  echo "Running data/$INPUT_FILE"

  valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./DictionaryTest "$INPUT_FILE"
done

make clean
```

For `Order.cpp`, I created a bash script to run a series of inputs and compared to the expected outputs to ensure the results were as expected.
```sh
#!/bin/bash
make

for i in "$@"; do  # Loop over all arguments passed to the script
  # Define file paths
  INPUT_FILE="../data/pa7/in$i.txt"
  EXPECTED_OUTPUT="../data/pa7/out$i.txt"
  ACTUAL_OUTPUT="../data/pa7/out.txt"

  # Run Sparse and save the output to out.txt
  echo "Running data/$INPUT_FILE"

  valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./Order "$INPUT_FILE" "$ACTUAL_OUTPUT"

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

## Speed of Program:
To ensure the program was as optimal as I could make it. I used `<chrono>` as a stopwatch to clock the times of various operation times.

## Compilation:

The make file compiles the code with the following flags to ensure consistency:
```
g++ -Wall -g -std=c++17 -c
```
