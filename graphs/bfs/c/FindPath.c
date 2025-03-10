/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file FindPath.c
 * @brief use the Graph ADT to find shortest paths between pairs of vertices
 * @param input_file the file name for the input file
 * @param output_file the file name for the output file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

#define MAX_STRING_LENGTH 100

// Handle generic failures
void handleFailure(const char* message) {
  fprintf(stderr, "ERROR: %s\n", message);
  exit(EXIT_FAILURE);
}

// typedef struct Path {
//   int* path;
//   int distance;
// } Path;

int getGraphSize(FILE* file) {
  int n = -1;
  if (fscanf(file, "%d", &n) != 1) {
    fclose(file);
    handleFailure("Failed to read the first number.");
  }
  return n;
}

// Create a string array of length n and read in the lines of the file as
// strings, placing them into the array.
void getGraphEdges(Graph G, FILE* file) {
  int u = -1;
  int v = -1;
  while (fscanf(file, "%d %d", &u, &v) == 2 && u != 0 && v != 0) {
    addEdge(G, u, v);
  }
}

void getGraphPaths(Graph G, FILE* file, FILE* out) {
  int start = -1;
  int end = -1;
  List L = newList();
  while (fscanf(file, "%d %d", &start, &end) == 2 && start != 0 && end != 0) {
    BFS(G, start);
    int d = getDist(G, end);
    if (d == INF) {
      fprintf(out, "The distance from %d to %d is infinity\n", start, end);
      fprintf(out, "No %d-%d path exists\n", start, end);
    } else {
      fprintf(out, "The distance from %d to %d is %d\n", start, end, d);
      clear(L);
      getPath(L, G, end);
      fprintf(out, "A shortest %d-%d path is: ", start, end);
      printList(out, L);
      fprintf(out, "\n");
    }
  }
  freeList(&L);
}

// main function
int main(int argc, char** argv) {
  if (argc != 3) handleFailure("Expected two arguements!");
  char* inputFileName = argv[1];
  char* outputFileName = argv[2];
  FILE* inputFile = fopen(inputFileName, "r");
  if (inputFile == NULL) {
    fclose(inputFile);
    handleFailure("Failure to read lines");
  }

  int n = getGraphSize(inputFile);

  if (n == -1) {
    fclose(inputFile);
    handleFailure("Failure to get size");
  }

  Graph G = newGraph(n);

  // open output file
  FILE* outputFile = fopen(outputFileName, "w");
  if (outputFile == NULL) {
    fclose(outputFile);
    handleFailure("No output file exists!");
  }

  // get adjacency list
  getGraphEdges(G, inputFile);
  printGraph(outputFile, G);
  fprintf(outputFile, "\n");

  // get paths
  getGraphPaths(G, inputFile, outputFile);
  fclose(inputFile);
  fclose(outputFile);

  // free the allocated memory
  freeGraph(&G);
  return 0;
}
