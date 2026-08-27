#include <stdio.h>

/*
    Question 1: Find All Unique Combinations

    Given an array of positive integers arr[] and a target sum x,
    find all unique combinations whose sum is equal to x.
    The same element can be selected unlimited number of times.
*/

int found = 0;


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


/* Function to sort the array in ascending order */
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


/*
    Function to find all possible combinations.

    res[] stores the current combination.
    target stores the remaining sum.
    index ensures that elements are selected
    in non-decreasing order.
*/
void find_combinations(int arr[], int n, int target,
                       int res[], int res_size, int index){

    // Target becomes zero, so a valid combination is found
    if(target==0){
        output(res, res_size);
        found=1;
        return;
    }

    for(int i=index;i<n;i++){

        // Since array is sorted, no further element can be used
        if(target<arr[i])
            break;

        res[res_size] = arr[i];

        /*
            Pass i again instead of i+1 because
            the same element can be selected multiple times.
        */
        find_combinations(arr, n, target-arr[i],
                          res, res_size+1, i);
    }
}


int main(){

    int arr[100], res[100], x;
    int n;

    // Input size of array
    printf("\nEnter size of the array: ");
    scanf("%d", &n);

    // Input array elements
    input(arr, n);

    // Input target value
    printf("\nEnter target value: ");
    scanf("%d", &x);

    // Sorting is required for ordered combinations
    sort(arr, n);

    // Find and display all combinations
    find_combinations(arr, n, x, res, 0, 0);

    // Print Empty if no combination is possible
    if(found==0)
        printf("Empty\n");

    return 0;
}