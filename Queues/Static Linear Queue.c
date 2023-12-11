#include<stdio.h>
#define maxSize 50
int rear=0,front=0;
// Function to check if queue is full
int isFull(int rear){
    // Check if rear equals maximum size
    if(rear==maxSize) return 1;
    return 0;
}
int isEmpty(int front,int rear){
    if(front==rear) return 1;
    return 0;
}
void enqueue(int a[],int rear,int data){
    if(isFull(rear)){
        printf("Overflow!"); return;
    }
}