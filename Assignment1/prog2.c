#include <stdio.h>

void input(int arr[], int n){
	printf("Enter %d element of array\n", n);
	for(int i=0;i<n;i++)
	scanf("%d", &arr[i]);
}
void output(int arr[], int n){
	printf("\n[");
	for(int i=0;i<n;i++){
		if(i!=0)
			printf(", ");
		printf("%d", arr[i]);
	}
	printf("]\n"); 	 	
}
void rotate(int arr[], int n, int d, int res[]){
	for(int i=0;i<n;i++){
		res[i] = arr[(i+d)%n]; 	 	
	}
}

int main(){
	int arr[100], res[100], n, d;
	printf("\nEnter size of the array: ");
	scanf("%d", &n);
	
	input(arr, n);
	printf("\nEnter d value: ");
	scanf("%d", &d);
	output(arr, n);
	rotate(arr, n, d, res);
	output(res, n);
	return 0;
}
