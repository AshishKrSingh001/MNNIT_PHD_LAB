#include<stdio.h>
#include<stdlib.h>

/* Function to take array input */
void input(int arr[], int n){
    printf("Enter %d element of array\n", n);

    for(int i=0;i<n;i++)
        scanf("%d", &arr[i]);
}


/* Function to display an array */
void output(int arr[], int n){
    printf("\n[");

    for(int i=0;i<n;i++){
        if(i!=0)
            printf(", ");

        printf("%d", arr[i]);
    }

    printf("]\n");
}

void heapify(int arr[], int n, int i){
	int largest = i;
	int left = 2*i+1;
	int right = 2*i+2;
	if(left<n && arr[left]>arr[largest])
		largest = left;
	if(right<n && arr[right]>arr[largest])
		largest = right;
	
	if(i!=largest){
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n){
	for(int i=n/2-1;i>=0;i--){
		heapify(arr, n, i);
	}
	for(int i=n-1;i>0;i--){
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapify(arr, i, 0);
	}
}

int main(){
	int arr[100], n;
	printf("\nEnter size of the array: ");
	scanf("%d", &n);
	input(arr, n);
	output(arr, n);
	heapSort(arr, n);
	output(arr, n);
	return 0;
}