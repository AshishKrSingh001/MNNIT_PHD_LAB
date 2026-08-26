#include <stdio.h>

int found=0;

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
void sort(int arr[], int n){
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(arr[i]>arr[j]){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
void find_combinations(int arr[], int n, int target, int res[], int res_size, int index){
	if(target==0){
		output(res, res_size);
		found=1;
		return;
	}
	for(int i=index;i<n;i++){
		if(target<arr[i]){
			break;
		}
		res[res_size] = arr[i];
		find_combinations(arr, n, target-arr[i], res, res_size+1, i);
	}
}


int main(){
	int arr[100], res[100], x; 
	int n;
	printf("\nEnter size of the array: ");
	scanf("%d", &n);
	
	input(arr, n);
	printf("\nEnter target value: ");
	scanf("%d", &x);
	//output(arr, n);
	sort(arr, n);
	//output(arr, n);
	find_combinations(arr, n, x, res, 0, 0);
	return 0;
}
