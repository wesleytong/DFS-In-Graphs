/****************************************************************************************
*  Wesley Tong
*  PA5
*  wtong5
*  Graph.c
*  Implemetation file for Graph ADT
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
//#include "List.h"

#define WHITE 1
#define GREY 2
#define BLACK 3


typedef struct GraphObj{
  List *adjacencyList;
  int *color;
  int *parent;
  int *discover;
  int *finish;
  int order;
  int size;
}GraphObj;

//Constructors/Destructors
//newGraph - Creates and returns a Graph with n vertices and no edges
Graph newGraph(int n){
  Graph G = malloc(sizeof(GraphObj));
  G->adjacencyList = malloc(sizeof(List)*(n+1));
  G->color = malloc(sizeof(int)*(n+1));
  G->parent = malloc(sizeof(int)*(n+1));
  G->discover = malloc(sizeof(int)*(n+1));
  G->finish = malloc(sizeof(int)*(n+1));
  G->order = n;
  G->size = 0;

  //need to also add loop to set the default settings
  for(int i = 0; i <= n; i++){
    G->adjacencyList[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
  return G;
}

//freeGraph - Frees all dynamic memory associated with Graph and sets *pG to NULL
void freeGraph(Graph* pG){
  //for()
  if(pG!=NULL && *pG!=NULL){
    for(int i = 0; i < ((*pG)->order+1); i++){
      freeList(&(*pG)->adjacencyList[i]);
    }
  }
  free((*pG)->adjacencyList);
  free((*pG)->color);
  free((*pG)->parent);
  free((*pG)->discover);
  free((*pG)->finish);
  free(*pG);
  *pG = NULL;
}

//Access Functions
//getOrder - Returns order
int getOrder(Graph G){
  if(G==NULL){
    printf("Graph Error: Calling getOrder() on a NULL Graph");
    exit(1);
  }
  return G->order;
}

//getSize - Returns size
int getSize(Graph G){
  if(G==NULL){
    printf("Graph Error: Calling getOrder() on a NULL Graph");
    exit(1);
  }
  return G->size;
}

//int getParent(Graph G, int u) - Gets the parent at vertex u. Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: Calling getParent() on a NULL Graph");
    exit(1);
  }
  //failing test script with if(u >= 1 && u <= getOrder(G)) - use exit cond instead
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: Calling getParent() out of bounds");
    exit(1);
  }
  return G->parent[u];
}

//int getDiscover(Graph G, int u) - Returns discovery time at vertex u. Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: Calling getDiscover() on a NULL Graph");
    exit(1);
  }
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: Calling getDiscover() out of bounds");
    exit(1);
  }
  return G->discover[u];
}

//int getFinish(Graph G, int u) - Returns finish time at vertex u. Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: Calling getFinish() on a NULL Graph");
    exit(1);
  }
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: Calling getFinish() out of bounds");
    exit(1);
  }
  return G->finish[u];
}

//void addEdge(Graph G, int u, int v) - Inserts a new edge joining u to v (u is the adjacency list of v, and v to the adjacency list of u). pre: 1 <= u <= getOrder(G)
void addEdge(Graph G, int u, int v){
  if(G==NULL){
    printf("Graph Error: Calling addEdge() on a NULL Graph");
    exit(1);
  }
  if( u < 1 || u > getOrder(G)){
      printf("Graph Error: Graph Vertices is out of bounds");
      exit(1);
    }

    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}
//void addArc(Graph G, int u, int v) - Inserts a new directed edge from u to v. pre: 1 <= u <= getOrder(G)
void addArc(Graph G, int u, int v){
  if(G==NULL){
    printf("Graph Error: Calling addEdge() on a NULL Graph");
    exit(1);
  }
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: Graph Vertices is out of bounds");
    exit(1);
  }
  if( v < 1 || v > getOrder(G)){
    printf("Graph Error: Graph Vertices is out of bounds");
    exit(1);
  }
  //printf("MoveFront in addArc");
  moveFront(G->adjacencyList[u]);
  //moves to right spot for append
  while(index(G->adjacencyList[u]) > -1 && v > get(G->adjacencyList[u])){
    moveNext(G->adjacencyList[u]);
  }
  if(index(G->adjacencyList[u]) == -1){
    append(G->adjacencyList[u], v);
  }
  else{
    insertBefore(G->adjacencyList[u], v);
  }
  G->size++;
}

//void DFS(Graph G, List s) - runs DFS algorithm on Graph G with source S.
//based on pseudocode provided
void DFS(Graph G, List S){
  if(G==NULL){
    printf("Graph Error: Calling BFS() on a NULL Graph");
    exit(1);
  }
  //creates default values (similar to newGraph)
  for(int i = 1; i <= G->order; i++){
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }

  moveFront(S);

  int time = 0; //local variable to hold time
  while(index(S) != -1){
    if(G->color[get(S)] == WHITE){
      Visit(G, S, get(S), &time);
    }
    moveNext(S);
  }

  //deletes value from stack
   for(int i = 0; i < G->order; i++){
     deleteBack(S);
   }
}

//void Visit(Graph G, List S, int u, int *time) - Helper function for visit in DFS, based off of CLRS pseudocode.
void Visit(Graph G, List S, int u, int *time){
  G->color[u] = GREY;
  *time = *time+1;
  G->discover[u] = *time;

  moveFront(G->adjacencyList[u]);
  while(index(G->adjacencyList[u]) != -1){
    //recursive if white
    if(G->color[get(G->adjacencyList[u])] == WHITE){
      G->parent[get(G->adjacencyList[u])] = u;
      Visit(G, S, get(G->adjacencyList[u]), time);
    }
    moveNext(G->adjacencyList[u]);
  }
  G->color[u] = BLACK;

  *time = *time+1;
  G->finish[u]= *time;
  prepend(S, u);
}

//void printGraph(FILE* out, Graph G) - Prints out the graph
void printGraph(FILE* out, Graph G){
  if(G==NULL){
    printf("Graph Error: Calling printGraph() on a NULL Graph");
    exit(1);
  }
  for(int i = 1; i<=getOrder(G); i++){
    fprintf(out, "%d:", i);
    printList(out, G->adjacencyList[i]);
    fprintf(out, "\n");
  }
}

//Graph transpose(Graph G) - Transposes the graph.
Graph transpose(Graph G){
  if(G==NULL){
    printf("Graph Error: Calling transpose() on a NULL Graph");
    exit(1);
  }
  Graph temp = newGraph(G->order);
  //i CANNOT start from 0 - used as index
  for(int i = 1; i <= G->order; i++){
    moveFront(G->adjacencyList[i]);
    while(index(G->adjacencyList[i]) != -1){
      addArc(temp, get(G->adjacencyList[i]), i);
      moveNext(G->adjacencyList[i]);
    }
  }
  return temp;
}

//Graph copyGraph(Graph G) - Copies the graph.
Graph copyGraph(Graph G){
  if(G==NULL){
    printf("Graph Error: Calling printGraph() on a NULL Graph");
    exit(1);
  }
  Graph copy = newGraph(G->order);
  copy->size = G->size;

  for(int i = 1; i <= G->order; i++){
    moveFront(G->adjacencyList[i]);
    if(index(G->adjacencyList[i])!= -1){
      addArc(copy, i, get(G->adjacencyList[i]));
      moveNext(G->adjacencyList[i]);
    }
  }
  return copy;
}
