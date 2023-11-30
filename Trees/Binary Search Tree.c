#include<stdio.h>
#include<stdlib.h>
struct Node{int key; struct Node *left, *right;};
struct Node *root=NULL;
int height(struct Node *root){
    if(root==NULL) return 0;
    int l=height(root->left), r=height(root->right);
    if(l>r) return l+1;
    return r+1;
}
struct Node *newNode(int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->key=data; node->left=NULL; node->right=NULL;
    return node;
}
struct Node *minNode(struct Node *root){
    struct Node *curr=root;
    while((curr && curr->left)!=NULL) curr=curr->left;
    return curr;
}
struct Node *maxNode(struct Node *root){
    struct Node *curr=root;
    while((curr && curr->right)!=NULL) curr=curr->right;
    return curr;
}
struct Node *insert(struct Node **root, int data){
    if((*root)==NULL)  (*root)=newNode(data);
    else if(data<(*root)->key) (*root)->left=insert(&(*root)->left,data);
    else if(data>(*root)->key) (*root)->right=insert(&(*root)->right,data);
    else printf("Duplicate Node!");
    return (*root);
}
struct Node *delete(struct Node **root, int data){
    if(root==NULL) return root; // Tree is empty
    if(data<(*root)->key) (*root)->left=delete(&((*root)->left),data); // Go left
    else if(data>(*root)->key) (*root)->right=delete(&((*root)->right),data); // Go right
    else{
        if((*root)->left==NULL){
            struct Node *temp=(*root)->right;
            free(root); return temp; // No left child, return right child
        }
        if((*root)->right==NULL){
            struct Node *temp=(*root)->left;
            free(root); return temp; // No right child, return left child
        }
        struct Node *temp=minNode((*root)->right); // Both children exist, replace root with min in right subtree
        (*root)->key=temp->key;
        (*root)->right=delete(&((*root)->right),temp->key); // Delete the replaced node in right subtree
    }
    return root;
}
void printGivenLevel(struct Node *root, int l){
    if(root==NULL) return;
    if(l==1) printf("%d",root->key);
    else{
        printGivenLevel(root->left,l-1);
        printGivenLevel(root->right,l-1);
    }
}
void levelorder(struct Node *root){
    for(int i=1;i<=height(root);i++){
        printGivenLevel(root,i); printf("\n");
    }
}
void preorder(struct Node *root){
    if(root!=NULL){
    printf("%d",root->key);
    preorder(root->left);
    preorder(root->right);
    }
}
void inorder(struct Node *root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d",root->key);
        inorder(root->right);
    }
}
void postorder(struct Node *root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d",root->key);
    }
}