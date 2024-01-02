#include<stdio.h>
struct Stack{int top;unsigned size;int *a;};
// Creating new stack with size
struct Stack *newStack(unsigned size){
    // Allocating memory for stack structure
    struct Stack *stack=(struct Stack*)malloc(sizeof(struct Stack));
    // Setting stack size and initializing top index
    stack->size=size; stack->top=-1;
    // Allocating memory for stack elements array
    stack->a=(int *)malloc(stack->size*sizeof(int));
    // Returning created stack
    return stack;
}
// Function to check if stack is full
int isFull(struct Stack *stack){
    // If top index is at the last position of stack
    // then it indicates stack is full
    return stack->top==stack->size-1; 
}
// check if stack is empty
int isEmpty(struct Stack *stack){
    // return 1 if top index is -1 (empty stack)
    return stack->top==-1;
}
void push(struct Stack *stack, int data) {
    // Check if stack is full before pushing
    if (isFull(stack)) {
        printf("Overflow!");
        return;
    }

    // Increment top and assign data to new top element
    stack->a[++(stack->top)] = data;
}
int pop(struct Stack *stack){
    // check if stack is empty
    if(isEmpty(stack)){
        printf("Underflow!"); return -1;
    }
    // return and decrement the top element
    return stack->a[stack->top--];
}
// Peek operation
int peek(struct Stack *stack){
    // Check if stack is empty
    if(isEmpty(stack)) {
        printf("Underflow!"); 
        return -1; // Return -1 if underflow occurs
    }
    // Return top element without removing it
    return stack->a[stack->top];
}
