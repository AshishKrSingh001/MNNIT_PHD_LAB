#include <stdio.h>
#define MAX_SIZE 100

void input(int mat[MAX_SIZE][MAX_SIZE], int n){
	printf("\nEnter %dX%d matrix element: \n", n,n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%d", &mat[i][j]);
		}
	}
}
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
	printf("\nIt is a Reflixive matrix");
}
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
	printf("\nEnter the size of the matrix\n");
	scanf("%d", &n);
	input(mat, n);
	output(mat, n);
	checkSymmetry(mat, n);
	checkReflexivity(mat, n);
	return 0;
}
