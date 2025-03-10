/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file Graph.h
 * @implements Graph ADT
 * @note program is required to maintain these lists in sorted order by
 * increasing labels
 */

#include "Graph.h"

#include <assert.h>
#include <stdlib.h>

/*** ERROR HANDLING ***/
void handleNullGraph(const char* message) {
  fprintf(stderr, "List Failure: %s on NULL List reference\n", message);
  exit(EXIT_FAILURE);
}

void handleGraphBoundsFailure(const char* message) {
  fprintf(stderr, "List Failure: %s - out of bounds\n", message);
  exit(EXIT_FAILURE);
}

// GraphObj type
typedef struct GraphObj {
  int v;      // verticies
  int e;      // edges
  int s;      // last accessed node
  int* p;     // parent array
  int* d;     // distance array
  int* c;     // color array
  List* adj;  // adjacency lists
} GraphObj;

/*** Constructors-Destructors ***/

/**
 * @implements newGraph()
 * @returns a Graph pointing to a newly created GraphObj
 * @brief represents a graph having n vertices and no edges.
 */
Graph newGraph(int n) {
  Graph G = (Graph)malloc(sizeof(GraphObj));
  assert(G != NULL);

  G->adj = (List*)malloc(sizeof(List) * n);
  assert(G->adj != NULL);
  for (int i = 0; i < n; i++) {
    G->adj[i] = newList();
  }

  G->v = n;
  G->e = 0;
  G->s = NIL;
  G->p = (int*)malloc(sizeof(int) * n);
  assert(G->p != NULL);
  G->d = (int*)malloc(sizeof(int) * n);
  assert(G->d != NULL);
  G->c = (int*)malloc(sizeof(int) * n);
  assert(G->c != NULL);
  return G;
}

/**
 * @implements freeGraph()
 * @brief frees all heap memory associated with the Graph *pG
 *        then sets the handle *pG to NULL
 */
void freeGraph(Graph* pG) {
  // free each array (p/d/c)
  free((*pG)->p);
  (*pG)->p = NULL;
  free((*pG)->d);
  (*pG)->d = NULL;
  free((*pG)->c);
  (*pG)->c = NULL;
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

/*** Access functions ***/

/**
 * @implements getOrder()
 * @returns value of order
 */
int getOrder(Graph G) {
  if (G == NULL) handleNullGraph("calling getOrder()");
  return G->v;
}

/**
 * @implements getSize()
 * @returns value of size
 */
int getSize(Graph G) {
  if (G == NULL) handleNullGraph("calling getSize()");
  return G->e;
}

/**
 * @implements getSource()
 * @returns source vertex most recently used in function BFS()
 *          or NIL if BFS() has not yet been called.
 */
int getSource(Graph G) {
  if (G == NULL) handleNullGraph("calling getSource()");
  return G->s;
}

/**
 * @implements getParent()
 * @returns parent of vertex u in the BFS tree created by BFS()
 *          or NIL if BFS() has not yet been called.
 * @pre 1 <= u <= getOrder(G)
 */
int getParent(Graph G, int u) {
  if (G == NULL) handleNullGraph("calling getParent()");
  if (u < 1 || u > getOrder(G)) handleGraphBoundsFailure("calling getParent()");
  return G->s != NIL ? G->p[u-1] : NIL;
}

/**
 * @implements getDist()
 * @returns distance from the most recent BFS source to vertex "u"
 *          or INF if BFS() has not yet been called.
 * @pre 1 <= u <= getOrder(G)
 */
int getDist(Graph G, int u) {
  if (G == NULL) handleNullGraph("calling getDist()");
  if (u < 1 || u > getOrder(G)) handleGraphBoundsFailure("calling getParent()");
  return G->s != NIL ? G->d[u - 1] : INF;
}

/**
 * @implements getPath()
 * @brief appends to the List L the vertices of a shortest path in G from source
 *        to u or appends to L the value NIL if no such path exists.
 * @pre getSource(G)!=NIL && 1 <= u <= getOrder(G) (BFS() must be called before
 *      getPath() is called)
 */
void getPath(List L, Graph G, int u) {
  if (G == NULL) handleNullGraph("calling getPath()");
  if (getSource(G) == NIL || u < 1 || u > getOrder(G)) {
    handleGraphBoundsFailure("calling getParent()");
  }
  if (isEmpty(L)) {
    // no path exists
    if (G->d[u-1] == INF) {
      prepend(L, NIL);
      return;
    }
    // back track to find the path!
    int cur = u;
    while (cur != NIL) {
      prepend(L, cur);
      cur = G->p[cur - 1];
    }
    return;
  }
  moveBack(L);
  // no path exists
  if (G->d[u-1] == NIL) {
    insertAfter(L, NIL);
    return;
  }
  // back track to find the path!
  int cur = u;
  while (cur != NIL) {
    insertAfter(L, cur);
    cur = G->p[cur - 1];
  }
  moveFront(L);
}

/*** Manipulation procedures ***/

/**
 * @implements makeNull()
 * @brief deletes all edges of G, restoring it to its original (no edge) state
 */
void makeNull(Graph G) {
  if (G == NULL) handleNullGraph("calling makeNull()");
  for (int i = 0; i < G->v; i++) { clear(G->adj[i]); }
  G->e = 0;
}

/**
 * @implements addEdge()
 * @brief inserts a new edge joining u to v
 *        ie: u is added to the adjacency List of v, and v to the adjacency List of u
 */
void addEdge(Graph G, int u, int v) {
  if (G == NULL) handleNullGraph("calling addEdge()");
  insertSorted(G->adj[u - 1], v);
  insertSorted(G->adj[v - 1], u);
  G->e++;
}

/**
 * @implements addArc()
 * @pre 1 <= u, v <= getOrder(G)
 */
void addArc(Graph G, int u, int v) {
  if (G == NULL) handleNullGraph("calling addArc()");
  if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
    handleGraphBoundsFailure("calling getParent()");
  }
  insertSorted(G->adj[u - 1], v);
  G->e++;
}

/**
 * @implements BFS()
 * @brief runs the BFS algorithm on the Graph G with source s
 *        setting the color, distance, parent, and source fields of G accordingly
 * @pre 1 <= s <= getOrder(G)
 */
void BFS(Graph G, int s) {
  if (G == NULL) handleNullGraph("calling BFS()");
  if (s < 1 || s > getOrder(G)) handleGraphBoundsFailure("calling getParent()");
  // set new source
  G->s = s;
  s--;
  // create default values
  for (int i = 0; i < G->v; i++) {
    G->c[i] = 0;    // undiscovered
    G->d[i] = INF;  // flag value
    G->p[i] = NIL;  // flag value
  }

  List q = newList();

  // initialization of the node we will search from (root)
  G->c[s] = 1;
  G->d[s] = 0;
  G->p[s] = NIL;
  append(q, s);

  // main section O(E)
  while (!isEmpty(q)) {
    int u = front(q);
    // get adjacency list
    List L = G->adj[u];
    moveFront(L);
    while (index(L) >= 0) {
      int v = get(L) - 1;
      if (G->c[v] == 0) {  // non-discovered node
        G->c[v] = 1;
        G->d[v] = G->d[u] + 1;
        G->p[v] = u + 1;
        append(q, v);
      }
      moveNext(L);
    }
    // done with it
    deleteFront(q);
    G->c[u] = 2;
  }
  freeList(&q);
}

/*** Other operations ***/
/**
 * @implements printGraph()
 * @brief prints the adjacency list representation of G to the file pointed to
 *        by out
 */
void printGraph(FILE* out, Graph G) {
  if (G == NULL) handleNullGraph("calling printGraph()");
  for (int i = 0; i < G->v; i++) {
    fprintf(out, "%d: ", i+1);
    if (!isEmpty(G->adj[i]))
      printList(out, G->adj[i]);
    else
      fprintf(out, "\n");
  }
}

/**
 * @implements printGraphToStdout()
 * @brief prints the adjacency list representation of G to stdout (in stdout)
 */
void printGraphToStdout(Graph G) {
  if (G == NULL) handleNullGraph("calling printGraph()");
  printf("PRINTING GRAPH:\n");
  for (int i = 0; i < G->v; i++) {
    if (!isEmpty(G->adj[i])) {
      printf("%d: ", i+1);
        printListToStdout(G->adj[i]);
    }
  }
  printf("Parents of each item:\n");
  for (int i = 0; i < G->v; i++) {
    if (G->p[i] != NIL)
      printf("%d: %d\n", i+1, G->p[i]);
  }
  printf("Distance of each item:\n");
  for (int i = 0; i < G->v; i++) {
    if (G->d[i] != INF)
      printf("%d: %d\n", i+1, G->d[i]);
  }
}


/**
 * @implements insertSorted()
 * @brief inserts the values in a sorted method
 */
void insertSorted(List L, int x) {
  if (isEmpty(L)) {
    append(L, x);
    return;
  }
  moveFront(L);
  while (index(L) >= 0 && get(L) < x) { moveNext(L); }
  index(L) < 0 ? append(L, x) : insertBefore(L, x);
}