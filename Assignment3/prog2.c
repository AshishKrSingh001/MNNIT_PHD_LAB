#include <stdio.h>

typedef struct PQ{
	int arr[100];
	int size;
}PQ;

void push(PQ *pq, int val){
	int i=pq->size-1;
	while(i>=0 && pq->arr[i]>val){
		pq->arr[i+1] = pq->arr[i];
		i--;
	}
	pq->arr[i+1] = val;
	pq->size++;
}
int pop(PQ *pq){
	if(pq->size==0)
	return -1;
	int val = pq->arr[pq->size-1];
	pq->size--;
	return val;
}
int top(PQ *pq){
	return (pq->size>0)?pq->arr[pq->size-1]:-1;
}
int main(){

	PQ pq;
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
