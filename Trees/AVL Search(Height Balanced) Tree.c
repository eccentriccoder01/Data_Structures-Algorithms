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
int bal(struct Node *root) {
   if(root == NULL) // If tree is empty, balance factor is 0
       return 0;
   return height(root->left) - height(root->right); // Subtract right subtree height from left subtree height
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
// Function to perform left rotation on the given root node
struct Node *LRot(struct Node *root) {
    // Store the right child of the root node
    struct Node *x = root->right;
    
    // Store the left child of the right child of the root node
    struct Node *T = root->right->left;
    
    // Make the right child of the root node as the new root
    x->left = root;
    
    // Make the left child of the right child of the root node as the right child of the root node
    root->right = T;
    
    // Update the height of the root node
    root->height = max(height(root->left), height(root->right)) + 1;
    
    // Update the height of the new root node
    x->height = max(height(x->left), height(x->right)) + 1;
    
    // Return the new root node
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