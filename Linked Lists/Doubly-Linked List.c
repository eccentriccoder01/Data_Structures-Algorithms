#include<stdio.h>
#include<stdlib.h>
struct Node{int info; struct Node *prev,*next;};
struct Node *start=NULL;
void insertFront(struct Node *start, int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->next=start; node->prev=NULL; node->info=data;
    start=node;
}
void append(struct Node *start, int data){
    struct Node *curr=start, *node=(struct Node*)malloc(sizeof(struct Node));
    node->info=data; node->next=NULL;
    if(start==NULL){
        start=node; return;
    }
    while(curr->next!=NULL) curr=curr->next;
    curr->next=node; node->prev=curr;
}
void insertAtP(struct Node *start, int p, int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node)), *curr=start;
    if(start==NULL){
        switch(p){ case 1: start=node; break;
        default: printf("Invalid Position!"); 
                 free(node);
                 return;
        }
    }
    else for(int i=0;i<p-2;i++) curr=curr->next;
    curr->next=node; node->prev=curr; node->next=curr->next; node->info=data;
}