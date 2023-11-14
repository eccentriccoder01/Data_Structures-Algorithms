#include<stdio.h>
#include<stdlib.h>
struct Node{int info; struct Node *link;};
struct Node *last=NULL;
struct Node *newNode(int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->info=data; node->link=NULL;
    return node;
}
int size(struct Node *last){
    struct Node *curr=last; int i=0;
    if(last!=NULL){
    do{ curr=curr->link; i++;
    }while(curr->!=last);
} return i;
}
void insertFront(struct Node **last, int data){
    struct Node *node=newNode(data);
    if(*last==NULL){
        *last=node; node->link=node;
        return;
    }
    node->link=(*last)->link; (*last)->link=node;
}
void append(struct Node **last, int data){
    struct Node *node=newNode(data);
    if((*last)==NULL){
        node->link=node; (*last)=node;
        return;
    }
    node->link=(*last)->link; (*last)->link=node; (*last)=node;
}
void insertAtP(struct Node **last, int p, int data){
    struct Node *curr=*last, *node=newNode(data);
    if(p>size(*last)+1){
        printf("Invalid Position!"); return;
    }
    if(*last==NULL){
        last=node; node->link=node;
    }
    for(int i=1;i<p;i++) curr=curr->link;
    node->link=curr->link; curr->link=node;
}
int deleteFront(struct Node **last){
    if(*last==NULL){
        printf("Underflow!"); return;
    }
    int data=(*last)->link->info;
    *last->next=(*last)->link->link;
    return data;
}
int pop(struct Node **last){
    if (*last==NULL){
        printf("Underflow"); return -1;
    }
    if((*last)->link==(*last)){
        free(*last); (*last)=NULL; return -1;
    }
    (*last)==()
}
