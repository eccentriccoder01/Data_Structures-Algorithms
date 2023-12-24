#include<stdio.h>
#include<stdlib.h>
struct Queue{int front,rear,size;unsigned capacity;int *a;};
// create new queue
struct Queue *newQueue(unsigned capacity){
    // allocate memory for queue structure
    struct Queue *q=(struct Queue*)malloc(sizeof(struct Queue));

    // initialize front and rear indices
    q->front==0;q->rear==capacity-1;

    // set initial size and capacity
    q->size=0;q->capacity=capacity;

    // allocate memory for queue array
    q->a=(int *)malloc(q->size*sizeof(int));

    return q;
}
int isFull(struct Queue *q){
    return q->size==q->capacity;
}
int isEmpty(struct Queue *q){
    return q->size==0;
}
void enqueue(struct Queue *q,int data){
    if(isFull(q)){
        printf("Overflow"); return;
    }
    q->a[++q->rear]=data;
}
int dequeue(struct Queue *q){
    if(isEmpty(q)){
        printf("Underflow!"); return -1;
    }
    q->
}