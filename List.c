/****************************************************************************************
*  Wesley Tong
*  PA5
*	 wtong5
*  List.c
*  Implementation file for List ADT
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
//#include <string.h>

//structs

//private NodeObj type
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int index; //returns the index the cursor is currently on and -1 if cursor undef, -1 should be default value of undefined index
	int length;
} ListObj;

//Constructors/Destructors

//newList(void) - Creates and returns a new empty list
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

//freeList() - Frees the heap memory associated with *pL, sets *pL to NULL
void freeList(List *pL){
	if(pL!= NULL && *pL!=NULL){
		while(length(*pL) > 0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

//Private functions for node

//Node newNode(int data) - Dynamically allocates a node and sets the links for the nodes as well as data.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj)); 	//dynamically allocates
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

//void freeNode(Node* pN) - Frees the node from the heap memory
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

//Access functions

//int length(List L) - Returns the number of elements in L
int length(List L){
	if(L == NULL){
		printf("List Error: Calling length() on NULL List Reference\n");
		exit(1);
	}
	return(L->length);
}

//int index(List L) - Returns index of cursor element if defined, -1 otherwise
int index(List L){
	if(L==NULL){
		return -1;
	}
	return(L->index);
}

//int front(List L) - Returns front element of L. Pre: length()>0
int front(List L){
	if(L==NULL){
		printf("List Error: Calling front() on NULL List reference\n");
		exit(1);
	}
	if(L->length<=0){
		printf("List Error: Calling front() on an empty List\n");
		exit(1);
	}
	return(L->front->data);
}

//int back(List L) - Returns back element of L. Pre: length()>0
int back(List L){
	if(L==NULL){
		printf("List Error: Calling back() on a NULL List reference\n");
		exit(1);
	}
	if(L->length<=0){
		printf("List Error: Calling back() on an empty list\n");
		exit(1);
	}
	return(L->back->data);
}

//int get(List L) - Returns the cursor element of L. Pre: length()>0, index()>=0
int get(List L){
	if(L==NULL){
		printf("List Error: Calling get() on a NULL List reference\n");
		exit(1);
	}
	if(L->length<=0){
		printf("List Error: Calling get() on an empty list\n");
		exit(1);
	}
	return(L->cursor->data);
}

//int equals(List A, List B) - Returns true (1) iff Lists A and B are in the same state, false (0) otherwise
int equals(List A, List B){
	int eq = 0;
	Node C = NULL;
	Node D = NULL;

	if( A == NULL || B == NULL){
		printf("List Error: Calling equals() on NULL List\n");
		exit(1);
	}

	eq = (A->length == B->length);
	C = A->front;
	D = B->front;
	while(eq && C!=NULL){
		eq = (C->data == D->data);
		C = C->next;
		D = D->next;
	}
	return eq;
}
//Manipulation procedures

//void clear(List L) - Resets L to its original empty state
void clear(List L){
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

//void moveFront(List L) - If L is not empty, sets cursor under front element, otherwise does nothing
void moveFront(List L){
	if(L==NULL){
		printf("List Error: Calling moveFront() on an NULL List reference\n");
		exit(1);
	}
	if(L->length!=0){
		L->cursor = L->front;
		L->index = 0;
	}
}

//void moveBack(List L) - If L is not empty, sets cursor under back element, otherwise does nothing
void moveBack(List L){
	if(L==NULL){
		printf("List Error: Calling moveBack() on an NULL List reference\n");
		exit(1);
	}
	if(L->length!=0){
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

//void movePrev(List L) - If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L){
	if(L==NULL){
		printf("List Error: Calling movePrev() on an NULL List reference\n");
		exit(1);
	}
	if(L->cursor != NULL && (L->cursor != L->front)){
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else if(L->cursor != NULL){ //this conditional checks if the cursor is defined
		L->cursor = NULL;
		L->index = -1;
	}
}

//void moveNext(List L) - If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L){
	if(L==NULL){
		printf("List Error: Calling moveNext() on a NULL List reference\n");
		exit(1);
	}
	if(L->cursor != NULL && (L->cursor != L->back)){
		L->cursor = L->cursor->next;
		L->index++;
	}
	else if(L->cursor != NULL){
		L->cursor = NULL;
		L->index = -1;
	}

}

//void prepend(List L, int data) - Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int data){
	if(L==NULL){
		printf("List Error: Calling prepend() on a NULL List reference\n");
		exit(1);
	}
	Node N = newNode(data);

	if(L->front == NULL){					//checks if L is non empty first
		L->front = L->back = N;
	}
	else{													//else inserts element into list
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		L->index++;
	}
	L->length++;
}
//void append(List L, int data) - Insert new element into L. If L is non-empty, insertion takes place after back element
void append(List L, int data){
	if(L==NULL){
		printf("List Error: Calling append() on a NULL List reference\n");
		exit(1);
	}
	Node N = newNode(data);

	if(L->back == NULL){				//checks if L is non empty first
		L->front = L->back = N;
	}
	else{
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
	}
	L->length++;
}

//void insertBefore(List L, int data) - Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int data){
	if(L==NULL){
		printf("List Error: Calling insertBefore() on an NULL List reference\n");
		exit(1);
	}
	if(L->length <= 0){
		printf("List Error: Calling insertBefore() on an empty list\n");
		exit(1);
	}
	if(L->index<0){ //index()>= 0
		printf("List Error: Calling insertBefore() on an invalid index\n");
		exit(1);
	}

	Node N = newNode(data);	//allocate new node
	if(L->cursor->prev != NULL){
		N->prev = L->cursor->prev;				//sets prev of new node to prev of original node
		L->cursor->prev->next = N;
		L->cursor->prev = N;
		N->next = L->cursor;
	}
	else {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}

	//L->cursor->prev = N;								//sets prev of original node to new node
	L->index++;
	L->length++;
}

//void insertAfter(List L, int data) - Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	if(L==NULL){
		printf("List Error: Calling insertAfter() on an NULL List reference\n");
		exit(1);
	}
	if(L->length <= 0){
		printf("List Error: Calling insertAfter() on an empty list\n");
		exit(1);
	}
	if(L->index<0){ //index()>= 0
		printf("List Error: Calling insertAfter() on an invalid index\n");
		exit(1);
	}

	Node N = newNode(data); //allocate new node
	if(L->cursor->next != NULL){
		N->next = L->cursor->next;				//sets prev of new node to prev of original node
		L->cursor->next->prev = N;
		L->cursor->next = N;
		N->prev = L->cursor;
	}
	else {
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}

	L->length++;
}

//void deleteFront(List L) - Delete the front element. Pre: length()>0
void deleteFront(List L){
	if(L==NULL){
		printf("List Error: Calling deleteFront() on an NULL List reference\n");
		exit(1);
	}
	if(L->length <= 0){
		printf("List Error: Calling deleteFront() on an empty list\n");
		exit(1);
	}

	//completely retooled - passed tests provided by TAs
	if(L->length>0){	//as long as list exists, will execute
		if(L->length ==1){	//if only one element - need to set ptrs to null and free data - sets back to default values
			Node N = L->front;
			L->cursor = NULL;
			L->front = NULL;
			L->back = NULL;
			L->index = -1;
			L->length = 0;
			freeNode(&N);
		}
		else{															//if more than one:
			if(L->cursor == L->front){			//check if cursor at front, if so set to NULL and index to -1
				L->cursor = NULL;
				L->index = -1;
			}
			else{														//otherwise just decrement the index
				L->index--;
			}

			//moving of pointers around to compensate for a deleted node
			Node N = L->front;
			L->front = N->next;
			N->next = NULL;
			L->front->prev = NULL;
			L->length--;
			freeNode(&N);
		}
	}
/* ---------- rewritten bc was failing tests - failed 3 tests for deletes
	Node N = NULL;
	if(L->index == 0){
		L->index = -1;
		L->cursor = NULL;
	}
	N = L->front; //sets node to front

	if(L->length > 1){
		L->front = L->front->next; //moves the next pointer to the new front
	}
	L->length--;
	freeNode(&N); 						//free the heap memory to prevent leaks
*/
}


//void deleteBack(List L) - Delete the back element. Pre: length()>0
void deleteBack(List L){
	if(L==NULL){
		printf("List Error: Calling deleteBack() on an NULL List reference\n");
		exit(1);
	}
	if(L->length <= 0){
		printf("List Error: Calling deleteBack() on an empty list\n");
		exit(1);
	}
	if(L->length > 0){					//similar idea as delete front but swapped around - refer to comments from those if needed
		if(L->length == 1){
			Node N = L->back;
			L->front = NULL;
			L->cursor = NULL;
			L->back = NULL;
			L->index = -1;
			L->length = 0;
			freeNode(&N);
		}
		else{
			if(L->cursor == L->back){
				L->cursor = NULL;
				L->index = -1;
			}

			Node N = L->back;
			L->back = N->prev;
			N->prev = NULL;
			L->back->next = NULL;
			L->length--;
			freeNode(&N);
		}
	}
	/* ----- rewritten because was failing tests
	Node N = NULL;

	N = L->back;
	if(L->length>1){
		L->back = L->back->prev;
	}
	else{
		L->front = L->back = NULL;
	}

	L->length--;
	N=NULL;
	freeNode(&N);					//free the heap memory to prevent leaks*/
}

//void delete(List L) - Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L){
	if(L==NULL){
		printf("List Error: Calling delete() on an NULL List reference\n");
		exit(1);
	}
	if(L->index < 0){
		printf("List Error: Calling delete on an invalid index\n");
		exit(1);
	}
	if(L->length <= 0){
		printf("List Error: Calling delete on an empty list\n");
		exit(1);
	}

	if (L->length > 0 && index(L) >= 0) {			//checks length and index to make sure that there's something to delete
		if(L->cursor == L->front){							//checks if cursor is at front; if so utilize already written method
			deleteFront(L);
		}
		else if(L->cursor == L->back){					//checks if cursor is at back, utilize already written method
			deleteBack(L);
		}
		else{
			Node left = L->cursor->prev;					//creates new nodes to hold the prev and next ptrs
			Node right = L->cursor->next;
			L->cursor->prev = NULL;								//sets next and prev to null (already held in the left/right ptr)
			L->cursor->next = NULL;
			left->next = right;										//accounts for the next ptr for both next and prev to link ptrs again
			right->prev = left;
			L->length--;
			L->index = -1;
			L->cursor = NULL;
			freeNode(&L->cursor);
		}
	}
}

//void printList(FILE* out, List L) - Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
	if(L==NULL){
		printf("List Error: Calling printList() on an NULL List reference\n");
		exit(1);
	}
	Node N = L->front;
	while(N!=NULL){										//loops through the list to print out the data members of each node
		fprintf(out, "%d ", N->data);		//note to self: fprintf is the function to print out to a file
		N = N->next;
	}
}

//List copyList(List L) - Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L){
	if(L==NULL){
		printf("List Error: Calling copyList() on an NULL List reference\n");
		exit(1);
	}
	List copy = newList();
	Node N = L->front;
	while(N!= NULL){
		append(copy, N->data);
		N = N->next;
	}
	return copy;
}
