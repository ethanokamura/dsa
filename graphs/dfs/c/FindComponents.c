/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file FindComponents.c
 * @brief Find the strongly connected components in a directed Graph ADT.
 */

#include <stdlib.h>

#include "Graph.h"

/**
 * @brief Generic function to handle failures.
 * @param message The error message to display.
 */
void handleFailure(const char* message) {
  fprintf(stderr, "ERROR: %s\n", message);
  exit(EXIT_FAILURE);
}

/**
 * @brief Validates file existance.
 * @param file The file to inspect.
 */
void validateFile(FILE* file) {
  if (file != NULL) return;
  handleFailure("FILE DOES NOT EXIST");
}

/**
 * @brief Builds the Graph ADT.
 * @param FILE The input file to be read from.
 * @returns A new Graph ADT.
 */
Graph buildGraph(FILE* file) {
  int n = -1;
  if (fscanf(file, "%d", &n) != 1) {
    fclose(file);
    handleFailure("Failed to read size.");
  }
  if (n == -1) handleFailure("Failure to get size.");
  Graph G = newGraph(n);
  int u = -1;
  int v = -1;
  while (fscanf(file, "%d %d", &u, &v) == 2 && u != 0 && v != 0) {
    addArc(G, u, v);
  }
  return G;
}

/**
 * @brief Prints the adjacency list of the Graph.
 * @param FILE The output file to write to.
 * @param G The Graph ADT.
 */
void printAdjacentNodes(FILE* file, Graph G) {
  printGraph(file, G);
  fprintf(file, "\n");
}

/**
 * @brief Builds an array of List ADTs.
 * @param n The number of SCC.
 */
List* buildListArr(int n) {
  List* arr = (List*)malloc(sizeof(List) * n);
  if (arr == NULL) handleFailure("Null list array!");
  for (int i = 0; i < n; i++) {
    arr[i] = newList();
    if (arr[i] == NULL) handleFailure("Null list array!");
  }
  return arr;
}

/**
 * @brief Frees the array of List ADTs.
 * @param n The number of SCC.
 */
void freeListArr(List** arr, int n) {
  if (arr == NULL || *arr == NULL) return;
  for (int i = 0; i < n; i++) {
    if ((*arr)[i] != NULL) {
      freeList(&((*arr)[i]));
      (*arr)[i] = NULL;
    }
  }
  free(*arr);
  *arr = NULL;
}

/**
 * @brief Extracts strongly connected vertices by their low link values.
 * @param G The Graph ADT.
 * @param L An array to store the strongly connected components.
 * @param S The stack holding the vertices in order of discover time.
 * @param n The number of SCC.
 */
void extractSCC(Graph G, List* L, List S, int n) {
  int ll = getLowLinkValue(G, front(S));
  while (!isEmpty(S)) {
    int v = front(S);
    if (ll != getLowLinkValue(G, v)) {
      n--;
      ll = getLowLinkValue(G, v);
    }
    append(L[n], v);
    deleteFront(S);
  }
}

/**
 * @brief Prints strongly connected components.
 * @param FILE The output file to write to.
 * @param L An array of List ADT's holding the vertices.
 * @param n The number of SCC.
 */
void printSCC(FILE* out, List* L, int n) {
  fprintf(out, "G contains %d strongly connected components:\n", n);
  int id = 0;
  for (int i = 0; i < n; i++) {
    if (!isEmpty(L[i])) {
      fprintf(out, "Component %d: ", ++id);
      while (!isEmpty(L[i])) {
        // print value
        fprintf(out, "%d ", front(L[i]));
        deleteFront(L[i]);
      }
      fprintf(out, "\n");
    }
  }
}

/**
 * @brief The main logic of the program that executes the following:
 *    1. Assembles the Graph ADT.
 *    2. Runs DFS(G) && DFS(G^T).
 *    3. Extracts strongly connected components (SCC) of G.
 *
 * @param argc The number of arguments.
 * @param argv An array of arguments.
 *
 * @note This takes 2 arguments:
 *    1. An input file
 *    2. An output file
 */
int main(int argc, char** argv) {
  // Get files
  if (argc != 3) handleFailure("Requires two arguements.");
  char* inputFileName = argv[1];
  char* outputFileName = argv[2];

  // Open and validate files
  FILE* inputFile = fopen(inputFileName, "r");
  validateFile(inputFile);
  FILE* outputFile = fopen(outputFileName, "w");
  validateFile(outputFile);

  // Create a new Graph ADT
  Graph G = buildGraph(inputFile);

  // Get the number of vertices for the Graph ADT
  int n = getOrder(G);

  // Create and output adjacency list
  printAdjacentNodes(outputFile, G);

  // Create a new List ADT
  // Append the ordered values for DFS traversal
  List S = newList();
  for (int i = 1; i <= n; i++) {
    append(S, i);
  }

  // Perform DFS(G) and DFS(G^T)
  DFS(G, S);
  Graph gT = transpose(G);
  DFS(gT, S);

  // Prepare, extract, and output Graph's SCC
  const int components = getComponentCount(gT);
  List* SCC = buildListArr(components);
  extractSCC(gT, SCC, S, components - 1);
  printSCC(outputFile, SCC, components);

  // Close files
  fclose(inputFile);
  fclose(outputFile);

  // Free the allocated memory
  freeGraph(&G);
  freeGraph(&gT);
  freeList(&S);
  freeListArr(&SCC, components);
  return 0;
}
