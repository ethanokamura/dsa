## How it works:
1. Assembles the `Dictionary` ADT.
2. Inserts keys with their original index as values into the `Dictionary`.
3. Outputs the calculations.

## Directory:

```
bst-2/
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
chmod +x ./tests/test_tester.sh
./tests/test_tester.sh 1 2 3
```

For `Order.cpp`, I created a bash script to run a series of inputs and compared to the expected outputs to ensure the results were as expected.
```sh
chmod +x ./tests/test_main.sh
./tests/test_main.sh 1 2 3
```

## Speed of Program:
To ensure the program was as optimal as I could make it. I used `<chrono>` as a stopwatch to clock the times of various operation times.

## Compilation:

The make file compiles the code with the following flags to ensure consistency:
```
g++ -Wall -g -std=c++17 -c
```
