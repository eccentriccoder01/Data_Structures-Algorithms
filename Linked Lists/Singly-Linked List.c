#include<stdio.h>
#include<stdlib.h>
struct Node{int info; struct Node *link;};
// Creating new node
struct Node *newNode(int data){
    // Allocating memory for the node
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));

    // Setting the node's data
    node->info=data;

    // Setting the node's link to NULL (initializing it)
    node->link=NULL;

    // Returning the newly created node
    return node;
}
void insertFront(struct Node **h, int data){
    // Allocate memory for new node
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    
    // Set new node's data and link
    node->info=data; node->link=*h;
    
    // Update head to point to new node
    *h = node;
}
void append(struct Node **h, int data){
    // Allocate memory for new node
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));

    // Assign data to new node and set next as NULL
    node->link=NULL; node->info=data;

    // If the list is empty, assign new node as head
    if(*h==NULL){
        *h=node; return;
    }

    // If list is not empty, traverse to last node
    struct Node *last = *h;
    while(last->next!=NULL){
        last=last->next; last->next=node;
    }
}
// Appends new node recursively
struct Node* appendRecursive(struct Node **h, int data){
    if(h==NULL) return newNode(data); // Create new node if head is null
    h->link=appendRecursive(h->link, data); // Recursive call for the next node
    return h; // Return updated head
}
void display(struct Node *h){
    while(h->link!=NULL){
        printf("%d",h->info);
        node=h->link;
    }
}
void displayRecursive(struct Node *h){
    if(h==NULL) return;
    printf("%d",h->info);
    displayRecursive(h->link);
}
static void reverse(struct Node **h){
    struct Node *prev=NULL, *curr=*h, *next=NULL;
    while(curr!=NULL){
        next=curr->link; curr->link=prev;
        prev=curr; curr->next; 
    }
    *h=prev;
}
void reverseDisplay(struct Node *h){
    struct Node *curr=h, *temp=NULL;
    while(curr!=NULL){
        struct Node *nextNode=curr->link;
        curr->link=temp; temp=curr; curr->nextNode;
    }
    while(temp!=NULL){
        printf("%d ->",curr->info);
        curr=curr->link;
    }
}