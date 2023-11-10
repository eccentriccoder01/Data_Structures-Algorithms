#include<stdio.h>
#include<stdlib.h>
struct Node{int info; struct Node *link;};
struct Node *newNode(int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->info=data; node->link=NULL;
    return node;
}
void insertFront(struct Node **h, int data){
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->info=data; node->link=*h;
    *h = node;
}
 void append(struct Node **h, int data){
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->link=NULL; node->info=data;
    if(*h==NULL){
    *h=node; return;
    }
    struct Node *last = *h;
    while(last->next!=NULL){
        last=last->next; last->next=node;
    }

}
struct Node* appendRecursive(struct Node **h, int data){
    if(h==NULL) return newNode(data);
    h->link=appendRecursive(h->link, data);
    return h;
}
void display(struct Node *h){
    while(h->link!=NULL){
        printf("%d",h->info);
        node=h->link;
    }
}
void displayRecursive