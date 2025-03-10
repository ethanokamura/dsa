#include <assert.h>
#include <stdlib.h>

#include "Graph.h"

/**
 * @brief Generic function to handle failures.
 * @param message The error message to display.
 */
void handleFailure(const char* message) {
  fprintf(stderr, "%s: FAILURE\n", message);
  exit(EXIT_FAILURE);
}

/**
 * @brief Generic function to handle success.
 * @param message The success message to display.
 */
void handleSucess(const char* message) { printf("%s: PASSED\n", message); }

/**
 * @brief Validates file existance.
 * @param file The file to inspect.
 */
void validateFile(FILE* file) {
  if (file != NULL) return;
  handleFailure("FILE DOES NOT EXIST");
}

/**
 * @brief Gets the size (orderOf) the Graph.
 * @param FILE The input file to be read from.
 */
int getGraphSize(FILE* file) {
  int n = -1;
  if (fscanf(file, "%d", &n) != 1) {
    fclose(file);
    handleFailure("Failed to read size.");
  }
  return n;
}

/**
 * @brief Gets the vertices and adds directed edges the Graph.
 * @param FILE The input file to be read from.
 * @param G The Graph ADT.
 * @param e The number of expected edges.
 */
int testSize(FILE* file, Graph G, int* e) {
  int u = -1;
  int v = -1;
  while (fscanf(file, "%d %d", &u, &v) == 2 && u != 0 && v != 0) {
    addArc(G, u, v);
    if (getSize(G) != ++(*e)) return -1;
  }
  return 0;
}

/**
 * @brief Asserts the correct parents for a given vertex.
 * @param FILE The input file to be read from.
 * @param G The Graph ADT.
 */
int testParents(FILE* file, Graph G) {
  int v = -1;
  int p = -1;
  while (fscanf(file, "%d %d", &v, &p) == 2 && v != 0 && p != 0) {
    if (getParent(G, v) != p) return -1;
  }
  return 0;
}

/**
 * @brief Asserts the correct parents for a given vertex.
 * @param FILE The input file to be read from.
 * @param G The Graph ADT.
 */
int testDiscoverTime(FILE* file, Graph G) {
  int v = -1;
  int d = -1;
  while (fscanf(file, "%d %d", &v, &d) == 2 && v != 0 && d != 0) {
    if (getDiscover(G, v) != d) return -1;
  }
  return 0;
}

/**
 * @brief Asserts the correct parents for a given vertex.
 * @param FILE The input file to be read from.
 * @param G The Graph ADT.
 */
int testFinishTime(FILE* file, Graph G) {
  int v = -1;
  int f = -1;
  while (fscanf(file, "%d %d", &v, &f) == 2 && v != 0 && f != 0) {
    if (getFinish(G, v) != f) return -1;
  }
  return 0;
}

// Provided by local grader (was giving me issues)
void DGgetSize() {
  Graph A = newGraph(100);
  List L = newList();
  assert(getSize(A) == 0);
  addArc(A, 54, 1);
  addArc(A, 54, 2);
  addArc(A, 54, 2);
  addArc(A, 54, 3);
  addArc(A, 1, 54);
  addArc(A, 1, 54);
  addArc(A, 1, 55);
  addArc(A, 1, 55);
  assert(getSize(A) == 5);
  for (int i = 1; i <= 100; i++) {
    append(L, i);
  }
  DFS(A, L);
  assert(getSize(A) == 5);
  addArc(A, 55, 1);
  assert(getSize(A) == 6);
  freeGraph(&A);
  freeList(&L);
}

/**
 * @brief Tests various methods inside Graph ADT
 * @param inputFile The formatted input file to read.
 */
void runAllTests(FILE* inputFile) {
  int n = getGraphSize(inputFile);
  int e = 0;
  Graph G = newGraph(n);
  List S = newList();
  for (int i = 1; i <= n; i++) {
    append(S, i);
  }
  assert(testSize(inputFile, G, &e) == 0);
  DFS(G, S);
  assert(getSize(G) == e);
  assert(testParents(inputFile, G) == 0);
  assert(testDiscoverTime(inputFile, G) == 0);
  assert(testFinishTime(inputFile, G) == 0);
  Graph gT = transpose(G);
  assert(getSize(G) == e);
  assert(getSize(gT) == e);
  DFS(gT, S);
  assert(getSize(gT) == e);
  assert(testParents(inputFile, gT) == 0);
  assert(testDiscoverTime(inputFile, gT) == 0);
  assert(testFinishTime(inputFile, gT) == 0);
  DGgetSize();
  freeGraph(&G);
  freeGraph(&gT);
  freeList(&S);
}

/**
 * @brief The main logic of the program that executes the following:
 *    1. Tests the assembly of the Graph ADT.
 *    2. Tests DFS(G) && DFS(G^T).
 *    3. Ensures correct / expected behaviour
 *    4. Handles success / failure
 *
 * @param argc The number of arguments.
 * @param argv An array of arguments.
 *
 * @note This takes an input file
 */
int main(int argc, char** argv) {
  if (argc != 2) handleFailure("Requires an input file.");
  char* inputFileName = argv[1];
  FILE* inputFile = fopen(inputFileName, "r");
  validateFile(inputFile);
  runAllTests(inputFile);
  handleSucess("ALL TESTS");
  fclose(inputFile);
  return 0;
}