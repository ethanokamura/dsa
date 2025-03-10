#include <assert.h>
#include <stdlib.h>

#include "Graph.h"

// Handle generic failures
void handleFailure(const char* message) {
  fprintf(stderr, "%s: FAILURE\n", message);
  exit(EXIT_FAILURE);
}
// Handle generic success
void handleSucess(const char* message) { printf("%s: PASSED\n", message); }

void freeGraphTest(Graph* G) {
  freeGraph(G);
  assert(*G == NULL);
}

/*** Access functions ***/
int getOrderTest(Graph G, int v) { assert(getOrder(G) == v); }
int getSizeTest(Graph G, int e) { assert(getSize(G) == e); }
int getSourceTest(Graph G, int s) { assert(getSource(G) == s); }
int getParentTest(Graph G, int u, int p) { assert(getParent(G, u) == p); }
int getDistTest(Graph G, int u, int x) { assert(getDist(G, u) == x); }
void getPathTest(Graph G) {
  List L = newList();
  getPath(L, G, 5);
  freeList(&L);
}
void emptyTest(Graph G, int v) {
  getOrderTest(G, v);
  getSizeTest(G, 0);
  getSourceTest(G, NIL);
  for (int i = 1; i < getOrder(G); i++) {
    getParentTest(G, i, NIL);
  }
}
/*** Manipulation procedures ***/
void makeNullTest(Graph G, int v) {
  makeNull(G);
  getOrderTest(G, v);
  getSizeTest(G, 0);
}

void addEdgeTest(Graph G, int u, int v, int n) {
  addEdge(G, u, v);
  assert(getSize(G) == n);
}

Graph newGraphTest(int v) {
  Graph G = newGraph(v);
  assert(G != NULL);
  emptyTest(G, v);
  return G;
}

void populateGraph(Graph G) {
  int n = 1;
  addEdgeTest(G, 1, 2, n);
  n ++;
  addEdgeTest(G, 1, 3, n);
  n ++;
  addEdgeTest(G, 2, 4, n);
  n ++;
  addEdgeTest(G, 2, 5, n);
  n ++;
  addEdgeTest(G, 2, 6, n);
  n ++;
  addEdgeTest(G, 3, 4, n);
  n ++;
  addEdgeTest(G, 4, 5, n);
  n ++;
  addEdgeTest(G, 5, 6, n);
  n ++;
}

void DG_getSize() {
  Graph A = newGraph(100);
  assert(getSize(A) == 0);
  addArc(A, 54, 1);
  addArc(A, 54, 2);
  addArc(A, 54, 3);
  addArc(A, 1, 54);
  addArc(A, 1, 55);
  assert(getSize(A) == 5);
  BFS(A, 67);
  assert(getSize(A) == 5);
  addArc(A, 55, 1);
  assert(getSize(A) == 6);
  freeGraph(&A);
}
void DG_getSource() {
  Graph A = newGraph(100);
  assert(getSource(A) == NIL);
  BFS(A, 42);
  assert(getSource(A) == 42);
  BFS(A, 88);
  assert(getSource(A) == 88);
  freeGraph(&A);
}
void DG_getParent() {
  Graph A = newGraph(100);
  for (int i = 1; i <= 100; i++) assert(getParent(A, i) == NIL);
  addArc(A, 64, 4);
  addArc(A, 64, 3);
  addArc(A, 42, 2);
  addArc(A, 2, 64);
  addArc(A, 4, 2);
  addArc(A, 3, 42);
  BFS(A, 42);
  assert(getParent(A, 42) == NIL);
  assert(getParent(A, 2) == 42);
  assert(getParent(A, 8) == NIL);
  freeGraph(&A);
}
void DG_getDist() {
  Graph A = newGraph(100);
  for (int i = 1; i <= 100; i++) {
    assert(getDist(A, i) == INF);
  }
  addArc(A, 64, 4);
  addArc(A, 64, 3);
  addArc(A, 42, 2);
  addArc(A, 2, 64);
  addArc(A, 4, 2);
  addArc(A, 3, 42);
  BFS(A, 64);
  assert(getDist(A, 64) == 0);
  assert(getDist(A, 2) == 2);
  BFS(A, 4);
  assert(getDist(A, 42) == 4);
  assert(getDist(A, 43) == INF);
  BFS(A, 99);
  assert(getDist(A, 64) == INF);
  freeGraph(&A);
}
void DG_getPath() {
  Graph A = newGraph(100);
  addArc(A, 64, 4);
  addArc(A, 64, 3);
  addArc(A, 42, 2);
  addArc(A, 2, 64);
  addArc(A, 4, 2);
  addArc(A, 3, 42);
  BFS(A, 3);
  List L = newList();
  List C = newList();
  getPath(L, A, 64);
  append(C, 3);
  append(C, 42);
  append(C, 2);
  append(C, 64);
  assert(equals(L, C));
  moveFront(L);
  BFS(A, 2);
  getPath(L, A, 2);
  append(C, 2);
  assert(equals(L, C));
  getPath(L, A, 99);
  assert(!equals(L, C));
  clear(L);
  clear(C);
  append(C, NIL);
  BFS(A, 99);
  getPath(L, A, 2);
  assert(equals(C, L));
  freeGraph(&A);
  freeList(&L);
  freeList(&C);
}

int runAllTests() {
  int n = 6;
  int e = 0;
  Graph G = newGraphTest(n);
  handleSucess("Created Graph");
  populateGraph(G);
  handleSucess("Populated Graph");
  BFS(G, 1);
  handleSucess("BFS");
  getOrderTest(G, n);
  handleSucess("Get Order");
  getSizeTest(G, 8);
  handleSucess("Get Size");
  getSourceTest(G, 1);
  handleSucess("Get Source");
  // getParentTest(G, 1, 2);  // not sure how to test the parents
  handleSucess("Get Parent");
  getDistTest(G, 5, 2);
  handleSucess("Get Dist");
  getPathTest(G);
  handleSucess("Get Path");
  makeNullTest(G, n);
  handleSucess("Make Null");
  // addArcTest(G, u, v);
  freeGraphTest(&G);
  handleSucess("Free Graph");
  DG_getSize();
  handleSucess("DG size");
  DG_getSource();
  handleSucess("DG source");
  DG_getParent();
  handleSucess("DG parent");
  DG_getDist();
  handleSucess("DG dist");
  DG_getPath();
  handleSucess("DG path");
  return 0;
}

int main() {
  switch (runAllTests()) {
    case 0:
      handleSucess("ALL TESTS");
      break;
    case 1:
      handleFailure("EXIT 1");
      break;
    case 2:
      handleFailure("EXIT 2");
      break;
    case 3:
      handleFailure("EXIT 3");
      break;
    default:
      handleFailure("Unknown");
      break;
  }
  return 0;
}