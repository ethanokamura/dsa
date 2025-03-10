/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file Graph.h
 * @def Graph ADT
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>

#include "List.h"

#define UNDEF -1  // INFINITE
#define NIL -2    // UNDEFINED VERTEX

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
int getLowLinkValue(Graph G, int u);
int getComponentCount(Graph G);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
int insertSorted(List L, int x);
void printGraph(FILE* out, Graph G);
void printGraphToStdout(Graph G);

#endif
