/****************************************************************************************
*  Wesley Tong
*  PA5
*  wtong5
*  Graph.h
*  Header file for Graph ADT
*****************************************************************************************/
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define UNDEF -1
#define NIL -2
#include <stdio.h>
#include "List.h"
typedef struct GraphObj* Graph;

//Constructors/Destructors
Graph newGraph(int n); //Creates and returns a Graph with n vertices and no edges
void freeGraph(Graph* pG); //Frees all dynamic memory associated with Graph and sets *pG to NULL

//Access Functions
int getOrder(Graph G); //returns order
int getSize(Graph G); //return size
int getParent(Graph G, int u); //Gets the parent at vertex u. Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u); //Returns discovery time at vertex u. Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u); //Returns finish time at vertex u. Pre: 1<=u<=n=getOrder(G)
//Manipulation Procedures
void addEdge(Graph G, int u, int v); //Inserts a new edge joining u to v (u is the adjacency list of v, and v to the adjacency list of u). pre: 1 <= u <= getOrder(G)
void addArc(Graph G, int u, int v); //Inserts a new directed edge from u to v. pre: 1 <= u <= getOrder(G)
void DFS(Graph G, List s); //runs DFS algorithm on Graph G with source S, setting color, distance, parent, and source fields of G.
void Visit(Graph G, List S, int u, int *time); //Helper function for visit in DFS, based off of CLRS pseudocode.

//Other operations
void printGraph(FILE* out, Graph G); //Prints out the graph
Graph transpose(Graph G); //Transposes the graph.
Graph copyGraph(Graph G); //Copies the graph.

#endif
