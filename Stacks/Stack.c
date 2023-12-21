#include<stdio.h>
struct Stack{int top;unsigned size;int *a;};
struct Stack *newStack(unsigned size){
    struct Stack *stack=(struct Stack*)malloc(sizeof(struct Stack));
    stack->size=size; stack->top=-1;
    stack->a=(int *)malloc(stack->size*sizeof(int));
    return stack;
}
int isFull(struct Stack *stack){
    return stack->top==stack->size-1; 
}
int isEmpty(struct Stack *stack){
    return stack->top==-1;
}
void push(struct Stack *stack,int data){
    if(isFull(stack)){
        printf("Overflow!"); return;
    }
    stack->a[++(stack->top)]=data;
}
int pop(struct Stack *stack){
    if(isEmpty(stack)){
        printf("Underflow!"); return -1;
    }
    return stack->a[stack->top--];
}
int peek(struct Stack *stack){
    if(isEmpty(stack)){
        printf("Underflow!"); return -1;
    }
    return stack->a[stack->top];
}
