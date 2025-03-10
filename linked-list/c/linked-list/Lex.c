/**
 * @author Ethan Okamura
 * @file Lex.c
 * @brief Main file for List ADT. Performs insertion sort
 * @status: working / tested
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

#define MAX_STRING_LENGTH 100

// Handle generic failures
void handleFailure(const char* message) {
  fprintf(stderr, "ERROR: %s\n", message);
  exit(EXIT_FAILURE);
}

// Count the number of lines n in the input file.
int getLineCount(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) handleFailure("No file exists!");
  int count = 0;
  char buffer[MAX_STRING_LENGTH];
  while (fgets(buffer, MAX_STRING_LENGTH, file)) {
    count++;
  }
  fclose(file);
  return count;
}

// Create a string array of length n and read in the lines of the file as
// strings, placing them into the array.
char** readLines(const char* filename, int* n) {
  FILE* file = fopen(filename, "r");
  char** stringArray = (char**)malloc(*n * sizeof(char*));
  if (stringArray == NULL || *n < 0 || file == NULL) {
    fclose(file);
    handleFailure("Failure to read lines");
  }
  // Read lines into the array
  char buffer[MAX_STRING_LENGTH];
  for (int i = 0; i < *n; i++) {
    if (fgets(buffer, MAX_STRING_LENGTH, file)) {
      // Remove trailing newline character
      buffer[strcspn(buffer, "\n")] = '\0';

      // Allocate memory for the string and copy it
      stringArray[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
      if (stringArray[i] == NULL) {
        fclose(file);
        handleFailure("Failure to allocate memory for string");
      }
      strcpy(stringArray[i], buffer);
    }
  }
  fclose(file);
  return stringArray;
}

// Inserts data into the Linked List using an insertion sort-like algorithm
void insertionSort(List L, char* arr[], int size) {
  append(L, 0);  // insert first element
  for (int i = 1; i < size; i++) {
    // move pointer to current index
    moveBack(L);
    while (index(L) >= 0 && strcmp(arr[get(L)], arr[i]) > 0) {
      movePrev(L);  // move backwards until the correct spot is found
    }
    // check if it surpassed the front of the list
    index(L) < 0 ? prepend(L, i) : insertAfter(L, i);
  }
}

// Function to free the allocated string array
void freeStringArray(char** arr, int n) {
  for (int i = 0; i < n; i++) {
    if (arr[i] != NULL) {
      free(arr[i]);
    }
  }
  free(arr);
}

int main(int argc, char** argv) {
  if (argc != 3) handleFailure("Expected two arguements!");
  char* inputFile = argv[1];
  char* outputFile = argv[2];

  // get number of lines
  int n = getLineCount(inputFile);

  // get strings for each line in the file
  char** lines = readLines(inputFile, &n);

  // init a new list
  List list = newList();

  // insertion sort - like insertion for List
  insertionSort(list, lines, n);

  // write sorted list to output file
  FILE* file = fopen(outputFile, "w");
  if (file == NULL) handleFailure("No output file exists!");
  for (moveFront(list); index(list) >= 0; moveNext(list)) {
    fprintf(file, "%s\n", lines[get(list)]);
  }

  // printList(file, list);
  fclose(file);

  // free the allocated memory
  freeList(&list);
  freeStringArray(lines, n);
  return 0;
}
