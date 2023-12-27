#include<stdio.h>
#include<stdlib.h>
struct Queue{int front,rear,size;unsigned capacity;int *a;};
// create new queue
struct Queue *newQueue(unsigned capacity){
    struct Queue *q=(struct Queue*)malloc(sizeof(struct Queue)); // allocate memory for queue structure
    q->front==0;q->rear==capacity-1;    // initialize front and rear indices
    q->size=0;q->capacity=capacity;    // set initial size and capacity
    q->a=(int *)malloc(q->size*sizeof(int));    // allocate memory for queue array
    return q;
}
// Function to check if the queue is full
int isFull(struct Queue *q){
    // Check if size equals capacity
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