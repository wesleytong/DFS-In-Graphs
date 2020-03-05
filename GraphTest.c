/****************************************************************************************
*  Wesley Tong
*  PA5
*  wtong5
*  GraphTest.c
*  Test File for Graph
*****************************************************************************************/
#include <stdio.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
  Graph G = newGraph(8);
  printf("Test Graph:\n");
  printf("Order    : %d\n", getOrder(G));
  printf("Size     : %d\n", getSize(G));
  printf("Discover : %d\n", getDiscover(G, 1));
  printf("Finish   : %d\n", getFinish(G, 1));
  printf("Parent   : %d\n", getParent(G, 1));

  addArc(G,1,2);
  addArc(G,1,7);
  addArc(G,2,4);
  addArc(G,3,5);
  addArc(G,3,7);
  addArc(G,4,5);
  addArc(G,5,7);
  addArc(G,7,8);
  addArc(G,8,3);
  printGraph(stdout, G);

  List L = newList();
  //running DFS
  for(int i = 1; i<= 8; i++){
    append(L, i);
  }
  DFS(G, L);
  for(int i = 1; i<= 8; i++){
    printf("Order    : %d\n", getOrder(G));
    printf("Size     : %d\n", getSize(G));
    printf("Discover : %d\n", getDiscover(G, i));
    printf("Finish   : %d\n", getFinish(G, i));
    printf("Parent   : %d\n", getParent(G, i));
  }

  Graph T = transpose(G);
  printGraph(stdout, T);
  Graph C = copyGraph(G);
  printGraph(stdout, G);

  freeList(&L);
  freeGraph(&G);
  freeGraph(&T);
  freeGraph(&C);
  return 0;
}
//Expected Output:
/*
Test Graph:
Order    : 8
Size     : 0
Discover : -1
Finish   : -1
Parent   : -2
1:2 7
2:4
3:5 7
4:5
5:7
6:
7:8
8:3
Order    : 8
Size     : 9
Discover : 1
Finish   : 14
Parent   : -2
Order    : 8
Size     : 9
Discover : 2
Finish   : 13
Parent   : 1
Order    : 8
Size     : 9
Discover : 7
Finish   : 8
Parent   : 8
Order    : 8
Size     : 9
Discover : 3
Finish   : 12
Parent   : 2
Order    : 8
Size     : 9
Discover : 4
Finish   : 11
Parent   : 4
Order    : 8
Size     : 9
Discover : 15
Finish   : 16
Parent   : -2
Order    : 8
Size     : 9
Discover : 5
Finish   : 10
Parent   : 5
Order    : 8
Size     : 9
Discover : 6
Finish   : 9
Parent   : 7
1:
2:1
3:8
4:2
5:3 4
6:
7:1 3 5
8:7
1:2 7
2:4
3:5 7
4:5
5:7
6:
7:8
8:3
*/
