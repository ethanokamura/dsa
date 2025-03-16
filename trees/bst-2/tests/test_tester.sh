#!/bin/bash
make DictionaryTest

for i in "$@"; do  # Loop over all arguments passed to the script
  # Define file paths
  INPUT_FILE="../data/in$i.txt"
  # Run Sparse and save the output to out.txt
  echo "Running data/$INPUT_FILE"

  valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./DictionaryTest "$INPUT_FILE"
done

make clean