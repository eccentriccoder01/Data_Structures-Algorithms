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
// Function to perform right rotation of the tree
struct Node *RRot(struct Node *root) {
    // Save the right child of the left child of root
    struct Node *x = root->left, *T = root->left->right;
    
    // Perform rotation
    x->right = root;    // Make x the new root
    root->left = T;     // Make T the left child of root
    
    // Update heights
    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    // Return the new root
    return x;
}
struct Node *LRot(struct Node *root){
    struct Node *x=root->right, *T=root->right->left;
    x->left=root; root->right=T;
    root->height=max(height(root->left),height(root->right))+1;
    x->height=max(height(x->left),height(x->right))+1;
    return x;
}
struct Node *insert(struct Node *root, int data){
    if(root==NULL){
        root=newNode(data); return;
    }
    if(data<root->key) root->left=insert(root->left,data);
    else if(data>root->key) root->right=insert(root->right,data);
    else return root;
    if(b>1 && data<root->left->key) return RRot(root);
    if(b<-1 && data>root->right->key) return LRot(root);
    if(b>1 && data>root->left->key){
        root->left=LRot(root->left);
        return RRot(root);
    }
    if(b<-1 && data<root->right->key){
        root->right=RRot(root->right);
        return LRot(root);
    }
    return root;
}