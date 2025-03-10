/**
 * @author Ethan Okamura
 * @file Graph.h
 * @implements Graph ADT
 */

#include "Graph.h"

#include <stdlib.h>

//#############################################//
//############## ERROR HANDLING ###############//
//#############################################//

/**
 * @brief Handles errors related to NULL graph references.
 * @param message The error message to display.
 */
void handleNullGraph(const char* message) {
  fprintf(stderr, "List Failure: %s on NULL List reference\n", message);
  exit(EXIT_FAILURE);
}

/**
 * @brief Handles errors related to graph bounds violations.
 * @param message The error message to display.
 */
void handleGraphBoundsFailure(const char* message) {
  fprintf(stderr, "List Failure: %s - out of bounds\n", message);
  exit(EXIT_FAILURE);
}

// GraphObj type
typedef struct GraphObj {
  int v;      // verticies
  int e;      // edges
  int s;      // DFS started flag
  int scc;    // scc count array
  int* p;     // parent array
  int* c;     // color array
  int* d;     // discover time array
  int* f;     // finish time array
  int* ll;    // low link array
  List* adj;  // adjacency lists
} GraphObj;

//#############################################//
//######## CONSTRUCTORS & DESTRUCTORS #########//
//#############################################//

/**
 * @brief Creates a new graph with n vertices and no edges.
 * @param n The number of vertices.
 * @return A new Graph ADT.
 */
Graph newGraph(int n) {
  // init graph
  Graph G = (Graph)malloc(sizeof(GraphObj));
  // init member variables
  G->v = n;
  G->e = 0;
  G->scc = 0;
  G->s = NIL;
  // init arrays
  G->p = (int*)malloc(sizeof(int) * n);
  G->c = (int*)malloc(sizeof(int) * n);
  G->d = (int*)malloc(sizeof(int) * n);
  G->f = (int*)malloc(sizeof(int) * n);
  G->ll = (int*)malloc(sizeof(int) * n);
  // init adjacency list
  G->adj = (List*)malloc(sizeof(List) * n);
  for (int i = 0; i < n; i++) {
    G->adj[i] = newList();
  }
  // handle null errors
  if (G == NULL || G->p == NULL || G->c == NULL || G->d == NULL ||
      G->f == NULL || G->ll == NULL || G->adj == NULL) {
    handleNullGraph("NULL data when creating a new graph");
  }
  // return new grpah
  return G;
}

/**
 * @brief Frees all memory associated with the given graph and sets it to NULL.
 * @param pG Pointer to the Graph to be freed.
 */
void freeGraph(Graph* pG) {
  // free each array (p/d/c)
  free((*pG)->p);
  (*pG)->p = NULL;
  free((*pG)->d);
  (*pG)->d = NULL;
  free((*pG)->f);
  (*pG)->f = NULL;
  free((*pG)->c);
  (*pG)->c = NULL;
  free((*pG)->ll);
  (*pG)->ll = NULL;
  // free adj
  for (int i = 0; i < (*pG)->v; i++) {
    freeList(&(*pG)->adj[i]);
    (*pG)->adj[i] = NULL;
  }
  free((*pG)->adj);
  (*pG)->adj = NULL;
  // free graph pG
  free(*pG);
  *pG = NULL;
}

//#############################################//
//############# ACCESS FUNCTIONS ##############//
//#############################################//

/**
 * @brief Public getter for the number of vertices in the graph.
 * @param G The Graph ADT.
 */
int getOrder(Graph G) {
  if (G == NULL) handleNullGraph("calling getOrder()");
  return G->v;
}

/**
 * @brief Public getter for the size of the graph.
 * @param G The Graph ADT.
 */
int getSize(Graph G) {
  if (G == NULL) handleNullGraph("calling getSize()");
  return G->e;
}

/**
 * @brief Public getter for a given node's parent.
 * @param G The Graph ADT.
 * @param u The vertex to check.
 */
int getParent(Graph G, int u) {
  if (G == NULL) handleNullGraph("calling getParent()");
  if (u < 1 || u > getOrder(G)) handleGraphBoundsFailure("calling getParent()");
  return G->s != NIL ? G->p[u - 1] : NIL;
}

/**
 * @brief Public getter for a given node's discover time.
 * @param G The Graph ADT.
 * @param u The vertex to check.
 */
int getDiscover(Graph G, int u) {
  if (G == NULL) handleNullGraph("calling getDiscover()");
  if (u < 1 || u > getOrder(G))
    handleGraphBoundsFailure("calling getDiscover()");
  return G->s != NIL ? G->d[u - 1] : UNDEF;
}

/**
 * @brief Public getter for a given node's finishing time.
 * @param G The Graph ADT.
 * @param u The vertex to check.
 */
int getFinish(Graph G, int u) {
  if (G == NULL) handleNullGraph("calling getDist()");
  if (u < 1 || u > getOrder(G)) handleGraphBoundsFailure("calling getFinish()");
  return G->s != NIL ? G->f[u - 1] : UNDEF;
}

/**
 * @brief Public getter for a given node's low link value.
 * @param G The Graph ADT.
 * @param u The vertex to check.
 */
int getLowLinkValue(Graph G, int u) {
  if (G == NULL) handleNullGraph("calling getDist()");
  if (u < 1 || u > getOrder(G))
    handleGraphBoundsFailure("calling getLowLinkValue()");
  return G->s != NIL ? G->ll[u - 1] : UNDEF;
}

/**
 * @brief Public getter for the number of strongly connected components.
 * @param G The Graph ADT.
 */
int getComponentCount(Graph G) {
  if (G == NULL) handleNullGraph("calling getDist()");
  return G->scc;
}

//#############################################//
//########## MANIPULATION PROCEDURES ##########//
//#############################################//

/**
 * @brief Adds an edge to an undirected graph.
 * @param G The Graph ADT.
 * @param u The first vertex.
 * @param v The second vertex.
 */
void addEdge(Graph G, int u, int v) {
  if (G == NULL) handleNullGraph("calling addEdge()");
  int res1 = insertSorted(G->adj[u - 1], v);
  int res2 = insertSorted(G->adj[v - 1], u);
  G->e += (res1 == 0 && res2 == 0) ? 1 : 0;
}

/**
 * @brief Adds an edge to a directed graph.
 * @param G The Graph ADT.
 * @param u The start vertex.
 * @param u The end vertex.
 */
void addArc(Graph G, int u, int v) {
  if (G == NULL) handleNullGraph("calling addArc()");
  if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
    handleGraphBoundsFailure("calling getParent()");
  }
  int res = insertSorted(G->adj[u - 1], v);
  if (res != 0)
    return;
  else
    G->e++;
}

/**
 * @brief Performs DFS visit recursively.
 * @param G The Graph ADT.
 * @param S The stack to hold the vertices when finished.
 * @param ll The value of the current low link.
 * @param x The value of the current vertex.
 * @param time A pointer to the algorithms time clock.
 */
void visit(Graph G, List S, int ll, int x, int* time) {
  G->d[x] = ++(*time);
  G->c[x] = 1;
  G->ll[x] = ll;
  moveFront(G->adj[x]);
  while (index(G->adj[x]) != -1) {
    int y = get(G->adj[x]) - 1;
    if (G->c[y] == 0) {
      G->p[y] = x + 1;
      visit(G, S, ll, y, &(*time));
    }
    moveNext(G->adj[x]);
  }
  insertAfter(S, x + 1);
  G->c[x] = 2;
  G->f[x] = ++(*time);
}

/**
 * @brief Performs depth-first search (DFS) on the graph.
 * @param G The Graph ADT.
 * @param S List defining the order in which vertices are processed.
 */
void DFS(Graph G, List S) {
  if (G == NULL) handleNullGraph("calling DFS()");
  if (length(S) != getOrder(G)) handleGraphBoundsFailure("calling DFS()");
  G->s = 1;
  for (int x = 0; x < G->v; x++) {
    G->c[x] = 0;
    G->p[x] = NIL;
  }
  G->scc = 0;
  int time = 0;
  int lastLowLink = 0;
  moveBack(S);
  while (index(S) != -1) {
    int x = front(S) - 1;
    if (G->c[x] == 0) {
      G->scc++;
      lastLowLink = x + 1;
      visit(G, S, lastLowLink, x, &time);
    }
    deleteFront(S);
  }
}

//#############################################//
//############# OTHER OPERATIONS ##############//
//#############################################//

/**
 * @brief Returns a copy of the current graph with inverted edges.
 * @param G The Graph ADT.
 * @return The new graph.
 */
Graph transpose(Graph G) {
  Graph gT = newGraph(G->v);
  for (int i = 0; i < G->v; i++) {
    moveFront(G->adj[i]);
    while (index(G->adj[i]) != -1) {
      addArc(gT, get(G->adj[i]), i + 1);
      moveNext(G->adj[i]);
    }
  }
  return gT;
}

/**
 * @brief Returns a copy of the current graph (without adjustments).
 * @param G The Graph ADT.
 * @return The new graph.
 */
Graph copyGraph(Graph G) {
  Graph nG = newGraph(G->v);
  for (int i = 0; i < G->v; i++) {
    nG->adj[i] = copyList(G->adj[i]);
  }
  nG->e = G->e;
  return nG;
}

/**
 * @brief Inserts a value into a given list with an insertion sort-like flow.
 * @param L The list ADT that the insertion is performed on.
 * @param x The value to be inserted.
 */
int insertSorted(List L, int x) {
  if (isEmpty(L)) {
    append(L, x);
    return 0;
  }
  moveFront(L);
  if (get(L) == x) return 1;
  while (index(L) >= 0 && get(L) < x) {
    if (get(L) == x) return 1;
    moveNext(L);
  }
  if (index(L) != -1 && get(L) == x) return -1;
  index(L) < 0 ? append(L, x) : insertBefore(L, x);
  return 0;
}

/**
 * @brief Prints out the adjacency list for the graph.
 * @param out The output file to write to.
 * @param G The graph ADT to be printed.
 */
void printGraph(FILE* out, Graph G) {
  if (G == NULL) handleNullGraph("calling printGraph()");
  fprintf(out, "Adjacency list representation of G:\n");
  for (int i = 0; i < G->v; i++) {
    fprintf(out, "%d: ", i + 1);
    if (!isEmpty(G->adj[i]))
      printList(out, G->adj[i]);
    else
      fprintf(out, "\n");
  }
}

/**
 * @brief Prints out the adjacency list, parents, discover time, and finish time
 * for the graph.
 * @param out The output file to write to.
 * @param G The graph ADT to be printed.
 */
void printGraphToStdout(Graph G) {
  if (G == NULL) handleNullGraph("calling printGraph()");
  printf("PRINTING GRAPH:\n");
  for (int i = 0; i < G->v; i++) {
    if (!isEmpty(G->adj[i])) {
      printf("%d: ", i + 1);
      printListToStdout(G->adj[i]);
    }
  }
  printf("Parents of each item:\n");
  for (int i = 0; i < G->v; i++) {
    if (G->p[i] != NIL) printf("%d: %d\n", i + 1, G->p[i]);
  }
  printf("discover time of each item:\n");
  for (int i = 0; i < G->v; i++) {
    if (G->d[i] != UNDEF) printf("%d: %d\n", i + 1, G->d[i]);
  }
  printf("finish time of each item:\n");
  for (int i = 0; i < G->v; i++) {
    if (G->f[i] != UNDEF) printf("%d: %d\n", i + 1, G->f[i]);
  }
}
