#include<stdio.h>
#include<stdlib.h>

struct node{
	int val;
	struct node *next;
};

struct node *h;

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

int is_empty(){
	return (h==NULL)?1:0;
}
void push(int val){
	struct node *p = (struct node*)malloc(sizeof(struct node));
	p->val = val;
	p->next = NULL;
	if(is_empty(h)){
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
int top(){
	if(is_empty(h)){
		return -1;
	}
	struct node *q;
	q=h;
	while(q->next!=NULL){
		q = q->next;
	}
	return q->val;
}
int pop(){
	if(is_empty(h)){
		return -1;
	}
	struct node *q;
	q=h;
	while(q->next->next!=NULL){
		q = q->next;
	}
	int x = q->next->val;
	q->next=NULL;
	return x;
}
void print_array(){
	if(is_empty(h)){
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

	printf("%d", is_empty());
	push(10);
	push(20);
	printf("%d", top());
	push(30);
	print_array();
	printf("%d", top());
	print_array();
	return 0;
}
