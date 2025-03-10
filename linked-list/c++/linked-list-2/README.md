# Programming Assignment 5

This assignment implements a doubly linked list in C++ and uses a List Abstract Data Type (ADT) to simulate a perfect shuffle of a deck of cards.

---

## Overview

This program uses a List ADT to perform a perfect shuffle. A perfect shuffle is simulated by following these steps:

1. **Split the Deck:**  
   The list representing the deck is divided into two halves.

2. **Merge the Halves:**  
   The two sub-decks are merged by alternating cards from each half.

3. **Determine Shuffle Count:**  
   For each subset of cards, the deck is repeatedly shuffled until the original order is restored. The program then outputs the number of shuffles required.

---

## Directory Structure

```
pa5/
├── List.cpp      # Implementation of the doubly linked list and its internal node structure.
├── List.h        # Definition of the doubly linked list and its methods.
├── ListTest.h    # Test cases for the List ADT functions.
├── Makefile      # Build script to compile and link all source files into a single executable.
├── README.md     # This file – description of the program and directory structure.
└── Shuffle.cpp     # Main logic for simulating the perfect shuffle.
```

---

## Testing

### Testing the List ADT

- **Purpose:**  
  Verify that all methods of the `List` class work as expected.
  
- **Approach:**  
  A suite of tests is executed to check consistency and correctness for operations such as insertion, deletion, and navigation.

### Testing the Shuffle Program

- **Purpose:**  
  Ensure that the perfect shuffle simulation produces the correct results and does not leak memory.

- **Approach:**  
  A Bash script runs the `Shuffle` executable under Valgrind. It compares the program’s output against expected output files.

- **Sample Test Script:**

  ```sh
  #!/bin/bash
  make

  for i in "$@"; do  # Loop over all arguments passed to the script
    # Define file paths
    EXPECTED_OUTPUT="data/out$i.txt"
    ACTUAL_OUTPUT="data/out.txt"

    echo "Running test with input: $i"

    # Run the program with Valgrind and save the output to out.txt
    valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./Shuffle $i > "$ACTUAL_OUTPUT"

    # Compare actual output with expected output
    if [ -f "$EXPECTED_OUTPUT" ]; then
      echo "Comparing output of $ACTUAL_OUTPUT with $EXPECTED_OUTPUT..."
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

---

## Compilation

The program is compiled with the following flags to ensure strict checking and compatibility:

```sh
g++ -Wall -Wextra -pedantic -g -std=c++17
```

These flags enable all warnings and extra warnings, enforce a strict standard, and include debug symbols.

