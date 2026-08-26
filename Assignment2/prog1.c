#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_CHILDREN 50
#define MAX_NODES 200
#define MAX_LINE 256

typedef struct Node{
	char name[MAX_NAME];
	int year;
	struct Node *childern[MAX_CHILDREN];
	int child_count;
	struct Node*parent;
}Node;
