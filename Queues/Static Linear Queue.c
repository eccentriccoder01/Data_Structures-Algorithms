#include<stdio.h>
#define maxSize 50
int rear=0,front=0;
int isFull(int rear){
    if(rear==maxSize) return 1;
    return 0;
}
int isEmpty(int front,int rear){
    if(front==rear) return 1;
    return 0;
}
void enqueue(int a[],int rear,int data){
    if(isFull(rear))
}