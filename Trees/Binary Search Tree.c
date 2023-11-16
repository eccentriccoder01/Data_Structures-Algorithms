#include<stdio.h>
#include<stdlib.h>
struct Node{int key; struct Node *left, *right;};
struct Node *root=NULL;
struct Node *newNode(int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->key=data; node->left=NULL; node->right=NULL;
    return node;
}
struct Node *insert(struct Node **root, int data){
    if((*root)==NULL)  (*root)=newNode(data);
    else if(data<(*root)->key) (*root)->left=insert(&(*root)->left,data);
    else if(data>(*root)->key) (*root)->right=insert(&(*root)->right,data);
    else printf("Duplicate Node!");
    return (*root);
}
struct Node *minNode(struct Node *root){
    struct Node *curr=root;
    while(curr && curr->left!=NULL) curr=curr->left;
    return curr;
}
