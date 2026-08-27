#include <stdio.h>

/*
    Question 2: Array Rotation

    Write a function rotate(arr[], d, n) that rotates
    an array of size n to the left by d positions.
*/


/* Function to take array input */
void input(int arr[], int n){
	printf("Enter %d element of array\n", n);

	for(int i=0;i<n;i++)
		scanf("%d", &arr[i]);
}


/* Function to display the array */
void output(int arr[], int n){
	printf("\n[");

	for(int i=0;i<n;i++){
		if(i!=0)
			printf(", ");

		printf("%d", arr[i]);
	}

	printf("]\n");
}


/*
    Function to rotate the array to the left by d positions.

    The formula (i+d)%n gives the index of the element
    that should come at position i in the rotated array.
*/
void rotate(int arr[], int n, int d, int res[]){

	for(int i=0;i<n;i++){
		res[i] = arr[(i+d)%n];
	}
}


int main(){

	int arr[100], res[100], n, d;

	// Input size of array
	printf("\nEnter size of the array: ");
	scanf("%d", &n);

	// Input array elements
	input(arr, n);

	// Input number of positions to rotate
	printf("\nEnter d value: ");
	scanf("%d", &d);

	// Display original array
	output(arr, n);

	// Perform left rotation
	rotate(arr, n, d, res);

	// Display rotated array
	output(res, n);

	return 0;
}