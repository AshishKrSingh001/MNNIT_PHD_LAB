#include <stdio.h>
#define MAX 100
typedef struct Job{
	int id;
	int rt;
}Job;
typedef struct PQ{
	struct Job jobs[MAX];
	int size;
}PQ;

void push(struct PQ *pq, struct Job job){
	int i = pq->size-1;
	while(i>=0 && pq->jobs[i].rt>job.rt){
		pq->jobs[i+1] = pq->jobs[i];
		i--;
	}
	pq->jobs[i+1] = job;
	pq->size++;
}
struct Job top(struct PQ *pq){
	return pq->jobs[0];
}
struct Job pop(struct PQ *pq){
	struct Job j = pq->jobs[0];
	for(int i=0;i<pq->size-1;i++){
		pq->jobs[i] = pq->jobs[i+1];
	}
	pq->size--;
	return j;
}
int empty(struct PQ *pq)
{
    return pq->size == 0;
}

int main(){
	struct PQ pq;
    pq.size = 0;

	Job j1 = {1, 8};
	Job j2 = {2, 3};
	Job j3 = {3, 5};
    push(&pq, j1);
    push(&pq, j2);
    push(&pq, j3);

    while(!empty(&pq)){
    	struct Job current = pop(&pq);
    	printf("\n\nJob: %d\nRemaining Time: %d\n\n", current.id, current.rt);
    	current.rt--;
    	if(current.rt>0){
    		push(&pq, current);
    	}else{
    		printf("\n\nJob: %d Finished", current.id);
    	}
    }
    return 0;
}
