#include <stdio.h>
#define MAX_SIZE 100

/*
    Question 4: Operations on Relations

    (a) Check whether the given relation matrix is reflexive.
    (b) Check whether the given relation matrix is symmetric.
*/


/* Function to take matrix input */
void input(int mat[MAX_SIZE][MAX_SIZE], int n){
	printf("\nEnter %dX%d matrix element: \n", n,n);

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d", &mat[i][j]);
		}
	}
}


/* Function to display the matrix */
void output(int mat[MAX_SIZE][MAX_SIZE], int n){
	printf("\nMatrix element: \n[");

	for(int i=0;i<n;i++){
		if(i!=0)
			printf(",\n");

		printf("[");

		for(int j=0;j<n;j++){
			if(j!=0)
				printf(", ");

			printf("%d", mat[i][j]);
		}

		printf("]");
	}

	printf("]");
}


/*
    A relation is reflexive if every diagonal
    element of the matrix is 1.

    For example:
    mat[0][0], mat[1][1], mat[2][2], ...
*/
void checkReflexivity(int mat[MAX_SIZE][MAX_SIZE], int n){

	if(n<=0){
		printf("\nInvalid Matrix");
		return;
	}

	for(int i=0;i<n;i++){

		if(mat[i][i]!=1){
			printf("\nNot a Reflexive Matrix");
			return;
		}
	}

	printf("\nIt is a Reflexive matrix");
}


/*
    A relation is symmetric if:
    
    mat[i][j] == mat[j][i]

    for every pair of elements.
*/
void checkSymmetry(int mat[MAX_SIZE][MAX_SIZE], int n){

	if(n<=0){
		printf("\nInvalid Matrix");
		return;
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){

			if(mat[i][j]!=mat[j][i]){
				printf("\nNot a Symmetric Matrix");
				return;
			}
		}
	}

	printf("\nIt is a Symmetric matrix");
}


int main(){

	int mat[MAX_SIZE][MAX_SIZE], n;

	// Input matrix size
	printf("\nEnter the size of the matrix\n");
	scanf("%d", &n);

	// Input and display matrix
	input(mat, n);
	output(mat, n);

	// Check both properties
	checkSymmetry(mat, n);
	checkReflexivity(mat, n);

	return 0;
}