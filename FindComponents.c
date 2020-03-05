/****************************************************************************************
*  Wesley Tong
*  PA5
*  wtong5
*  FindComponents.c
*  Implemetation file for FindComponents.c
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"
#define MAX_LEN 255

int main(int argc, char* argv[]){
  FILE *in, *out;
  char line[MAX_LEN];
  //checks command line for correct number of arguments
  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  int size;

  //reading in input
  fgets(line, MAX_LEN, in);
  sscanf(line, "%d", &size);

  //values of vertices put into a list
  List L = newList();
  for(int i = 1; i<=size; i++){
    append(L, i);
  }

  Graph G = newGraph(size);

  int u = 0;
  int v = 0;

	// -- fscanf is missing the first value of adjacency list but sscanf works
  while(fgets(line, MAX_LEN, in) != NULL){
    //fscanf(in, "%d %d", &u, &v);
    sscanf(line, "%d %d", &u, &v);
    if(u==0 && v == 0){
			break;
    }
		addArc(G, u, v);
  }

  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\n");

  DFS(G, L);
  //creates Transpose of Graph
  Graph T = transpose(G);
  DFS(T, L);

  //counts the number of strongly connected components of G, then prints - pt1 of PA5
  int scc = 0;
  for(int i = 1; i<=getOrder(T);i++){
    if(getParent(T,i) == NIL){
      scc++;
    }
  }
  fprintf(out, "G contains %d strongly connected components:\n", scc);

  //then creates list to store values (second stack)
  int counter = 1;
  List S = newList();
  moveBack(L);
  while(index(L) != -1){
    int val = get(L);
    prepend(S, val);
    //begins printing for second part of specs:
    //T->parent[val] does not work
    if(getParent(T, val)==NIL){
      fprintf(out, "Component %d: ", counter);
      printList(out, S);
      if(index(L)!=0){
        fprintf(out, "\n");
      }
      clear(S);
      counter++;
    }
    movePrev(L);
  }

  freeGraph(&G);
  freeGraph(&T);
  freeList(&L);
  freeList(&S);
  fclose(in);
  fclose(out);
  return 0;
}
