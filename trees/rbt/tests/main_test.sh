#!/bin/bash
make

for i in "$@"; do  # Loop over all arguments passed to the script
  # Define file paths
  INPUT_FILE="./data/in$i.txt"
  EXPECTED_OUTPUT="./data/out$i.txt"
  ACTUAL_OUTPUT="./data/out.txt"

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