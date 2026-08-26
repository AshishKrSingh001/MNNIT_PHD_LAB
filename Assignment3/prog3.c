#include<stdio.h>

typedef struct{
	int arr[100];
	int size;
}heap;

void heapify(heap *h, int i){
	int largest = i;
	int left = 2*i+1;
	int right = 2*i+2;
	
	if(left<h->size && h->arr[left]>h->arr[largest]){
		largest = left;
	}if(right<h->size && h->arr[right]>h->arr[largest]){
		largest = right;
	}if(largest!=i){
		int temp = h->arr[largest];
		h->arr[largest] = h->arr[i];
		h->arr[i] = temp;
		heapify(h, largest);
	}
}
void buildHeap(heap *h) {
    for (int i = h->size / 2 - 1; i >= 0; i--)
        heapify(h, i);
}
int deleteMax(heap *h) {
    if (h->size == 0)
        return -1;

    int max = h->arr[0];

    h->arr[0] = h->arr[h->size - 1];
    h->size--;

    heapify(h, 0);

    return max;
}
void printHeap(heap *h) {
    for (int i = 0; i < h->size; i++)
        printf("%d ", h->arr[i]);

    printf("\n");
}

int main() {
    heap h = {{11, 5, 17, 8, 9}, 5};
    printHeap(&h);
	buildHeap(&h);
	printHeap(&h);
	deleteMax(&h);
	printHeap(&h);
    return 0;
}
