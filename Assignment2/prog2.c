#include <stdio.h>

typedef struct node{
	int key;
	int height;
	struct node *left;
	struct node *right; 
}node;

int height(node *n){
	return (n==NULL)?0:n->height;
}

int max(int a, int b){
	return (a>=b)?a:b;
}
int balanceFactor(node *n){
	return (n==NULL)?0:height(node->left)-height(node->right);
}

int main(){
	return 0;
}
