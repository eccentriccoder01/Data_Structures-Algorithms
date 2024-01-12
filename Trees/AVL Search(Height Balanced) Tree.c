#include<stdio.h>
#include<stdlib.h>
struct Node{int key,height; struct Node *left,*right}
struct Node *newNode(int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->height=1; node->key=data;
    node->left=NULL; node->right=NULL;
    return node;
}
int max(int a, int b){
    return a>b ? a : b;
}
int height(struct Node *root){
    if(root==NULL) return 0;
    return root->height;
}
int bal(struct Node *root){
    if(root==NULL) return 0;
    return height(root->left) - height(root->right);
}
struct Node *RRot(struct Node *root){
    struct Node *x=root->left, *T1=root->left->right;
    x->right=root; root->left=T2;
    root->height=max(height(root->left),height(root->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
}