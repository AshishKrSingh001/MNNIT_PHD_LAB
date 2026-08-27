#include<stdio.h>

/*
    Question 3: Heap Property

    Implement:
    1. Heapify
    2. Build Heap
    3. Delete Max
*/

typedef struct{
	int arr[100];
	int size;
}heap;


/*
    Heapify maintains the max heap property
    for the subtree starting from index i.
*/
void heapify(heap *h, int i){

	int largest = i;

	int left = 2*i+1;
	int right = 2*i+2;


	// Check left child
	if(left<h->size && h->arr[left]>h->arr[largest]){
		largest = left;
	}

	// Check right child
	if(right<h->size && h->arr[right]>h->arr[largest]){
		largest = right;
	}


	// If child is larger, swap and heapify again
	if(largest!=i){

		int temp = h->arr[largest];
		h->arr[largest] = h->arr[i];
		h->arr[i] = temp;

		heapify(h, largest);
	}
}


/* Convert the given array into a max heap */
void buildHeap(heap *h){

	for(int i=h->size/2-1;i>=0;i--)
		heapify(h, i);
}


/* Remove and return the maximum element */
int deleteMax(heap *h){

	if(h->size==0)
		return -1;

	int max = h->arr[0];

	// Move last element to the root
	h->arr[0] = h->arr[h->size-1];

	h->size--;

	// Restore heap property
	heapify(h, 0);

	return max;
}


/* Display the heap */
void printHeap(heap *h){

	for(int i=0;i<h->size;i++)
		printf("%d ", h->arr[i]);

	printf("\n");
}


int main(){

	heap h = {{11, 5, 17, 8, 9}, 5};

	printf("Before Build Heap: ");
	printHeap(&h);

	buildHeap(&h);

	printf("After Build Heap: ");
	printHeap(&h);

	printf("Deleted Max: %d\n", deleteMax(&h));

	printf("After Delete Max: ");
	printHeap(&h);

	return 0;
}