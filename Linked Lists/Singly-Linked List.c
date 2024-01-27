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
    // Initialize pointer to first node
    while(h->link!=NULL){
        // Print node value
        printf("%d",h->info);
        // Move pointer to next node
        node=h->link;
    }
}
void displayRecursive(struct Node *h){
    // Check if head is null
    if(h==NULL) return;

    // Print node value
    printf("%d",h->info);

    // Recursive call for next node
    displayRecursive(h->link);
}
static void reverse(struct Node **h) {
    // Initialize previous, current, and next pointers
    struct Node *prev = NULL, *curr = *h, *next = NULL;

    // Iterate through the linked list
    while (curr != NULL) {
        // Save the next node in the list
        next = curr->link;
        // Reverse the link direction
        curr->link = prev;
        // Move to the next iteration
        prev = curr;
        curr = next;
    }

    // Update the head pointer to the new first node
    *h = prev;
}
void reverseDisplay(struct Node *h){
    struct Node *curr=h, *temp=NULL;

    // Iterate through the linked list
    while(curr!=NULL){
        struct Node *nextNode=curr->link;
        curr->link=temp; // Reverse the link direction
        temp=curr;        // Set the current node as the next temp node
        curr=nextNode;    // Move to the next node in the original list
    }

    // Iterate through the reversed linked list and print the values
    while(temp!=NULL){
        printf("%d ->",curr->info);
        curr=curr->link;
    }
}