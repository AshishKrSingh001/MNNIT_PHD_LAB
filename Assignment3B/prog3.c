#include <stdio.h>

#define MAX 100

/*
Q3. Priority Queue Using a 2D Array

Suppose we have a 2D array in which:
A(i,j) <= A(i+1,j)
A(i,j) <= A(i,j+1)

Can this 2D array be used to implement a priority queue?
Justify your answer.
*/

typedef struct {
    int arr[MAX][MAX];
    int rows;
    int cols;
} PriorityQueue;

// Display the 2D priority queue
void display(PriorityQueue *pq){
    int i,j;

    for(i=0;i<pq->rows;i++){
        for(j=0;j<pq->cols;j++)
            printf("%d\t",pq->arr[i][j]);
        printf("\n");
    }
}

// Return the minimum element
int top(PriorityQueue *pq){
    return pq->arr[0][0];
}

// Remove the minimum element
void pop(PriorityQueue *pq){
    int i=0,j=0;
    int down,right,temp;

    while(1){
        if(i+1<pq->rows)
            down=pq->arr[i+1][j];
        else
            down=999999;

        if(j+1<pq->cols)
            right=pq->arr[i][j+1];
        else
            right=999999;

        if(down==999999 && right==999999)
            break;

        if(down<right){
            pq->arr[i][j]=down;
            i++;
        }
        else{
            pq->arr[i][j]=right;
            j++;
        }
    }

    pq->arr[i][j]=999999;
}

// Main function
int main(){
    PriorityQueue pq;
    int choice;

    pq.rows=3;
    pq.cols=3;

    pq.arr[0][0]=1;
    pq.arr[0][1]=4;
    pq.arr[0][2]=7;
    pq.arr[1][0]=2;
    pq.arr[1][1]=5;
    pq.arr[1][2]=9;
    pq.arr[2][0]=3;
    pq.arr[2][1]=8;
    pq.arr[2][2]=12;

    while(1){
        printf("\n1. Top\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                printf("Minimum Priority = %d\n",top(&pq));
                break;

            case 2:
                if(pq.arr[0][0]==999999)
                    printf("Priority Queue is empty\n");
                else{
                    printf("Removing %d\n",pq.arr[0][0]);
                    pop(&pq);
                }
                break;

            case 3:
                display(&pq);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}