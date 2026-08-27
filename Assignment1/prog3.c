#include<stdio.h>
#include<stdlib.h>

/*
    Question 3: Stack Implementation Using Linked List

    Implement a stack using a linked list with the
    following operations:
    1. size()
    2. is_empty()
    3. push()
    4. top()
    5. pop()
*/

struct node{
	int val;
	struct node *next;
};

struct node *h = NULL;


/* Return the number of elements in the stack */
int size(){
	int count = 0;
	struct node *q;
	q=h;

	while(q!=NULL){
		count = count + 1;
		q=q->next;
	}

	return count;
}


/* Check whether the stack is empty */
int is_empty(){
	return (h==NULL)?1:0;
}


/* Insert an element at the top of the stack */
void push(int val){

	struct node *p = (struct node*)malloc(sizeof(struct node));

	p->val = val;
	p->next = NULL;

	if(is_empty()){
		h = p;
		return;
	}

	struct node *q;
	q=h;

	while(q->next!=NULL){
		q = q->next;
	}

	q->next = p;
}


/* Return the top element without removing it */
int top(){

	if(is_empty()){
		return -1;
	}

	struct node *q;
	q=h;

	while(q->next!=NULL){
		q = q->next;
	}

	return q->val;
}


/* Remove and return the top element */
int pop(){

	if(is_empty()){
		return -1;
	}

	// Special case: only one node is present
	if(h->next == NULL){
		int x = h->val;
		free(h);
		h = NULL;
		return x;
	}

	struct node *q;
	q=h;

	while(q->next->next!=NULL){
		q = q->next;
	}

	int x = q->next->val;

	free(q->next);
	q->next = NULL;

	return x;
}


/* Display all elements of the stack */
void print_array(){

	if(is_empty()){
		return;
	}

	struct node *q;
	q=h;

	printf("[");

	while(q!=NULL){
		if(q!=h){
			printf(", ");
		}

		printf("%d", q->val);
		q = q->next;
	}

	printf("]");
}


int main(){

	printf("Is empty: %d\n", is_empty());

	push(10);
	push(20);

	printf("Top: %d\n", top());

	push(30);

	printf("Stack: ");
	print_array();

	printf("\nTop: %d\n", top());

	printf("Popped: %d\n", pop());

	printf("Stack after pop: ");
	print_array();

	printf("\nSize: %d\n", size());

	return 0;
}