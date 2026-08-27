#include <stdio.h>

/*
    Question 2: Priority Queue Using an Unsorted Array

    The elements are stored in the array according
    to their priority.

    The maximum element is kept at the end so that
    top() and pop() can be performed in O(1).
*/

typedef struct PQ{
	int arr[100];
	int size;
}PQ;


/* Insert an element at its correct position */
void push(PQ *pq, int val){

	int i = pq->size-1;

	// Shift larger elements to the right
	while(i>=0 && pq->arr[i]>val){
		pq->arr[i+1] = pq->arr[i];
		i--;
	}

	pq->arr[i+1] = val;
	pq->size++;
}


/* Remove and return the highest priority element */
int pop(PQ *pq){

	if(pq->size==0)
		return -1;

	int val = pq->arr[pq->size-1];

	pq->size--;

	return val;
}


/* Return the highest priority element */
int top(PQ *pq){
	return (pq->size>0)?pq->arr[pq->size-1]:-1;
}


int main(){

	PQ pq;

	// Initially the priority queue is empty
	pq.size=0;

	push(&pq, 100);
	push(&pq, 1000);
	push(&pq, 10022);

	printf("\n%d", pop(&pq));
	printf("\n%d", top(&pq));
	printf("\n%d", pop(&pq));
	printf("\n%d", pop(&pq));

	return 0;
}