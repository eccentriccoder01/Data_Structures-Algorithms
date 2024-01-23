#include<stdio.h>
#include<stdlib.h>
struct Node{int key,height; struct Node *left,*right}
// Function to create a new node with given data
struct Node *newNode(int data) {
    // Allocate memory for new node
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    
    // Assign data to the node
    node->key = data;
    
    // Initialize height of the node as 1
    node->height = 1;
    
    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;
    
    // Return the newly created node
    return node;
}
int max(int a, int b){
    return a>b ? a : b;
}
// Function to get height of tree
int height(struct Node *root)  // Input: node of the tree
{  				 // Output: height of the tree
   if(root==NULL) return 0;  // Return 0 if tree is empty
   return root->height;  // Return height if node is not NULL
}
int bal(struct Node *root) {
   if(root == NULL) // If tree is empty, balance factor is 0
       return 0;
   return height(root->left) - height(root->right); // Subtract right subtree height from left subtree height
}
// Function to perform right rotation of the tree
struct Node *RRot(struct Node **root) {
    // Save the right child of the left child of root
    struct Node *x = (*root)->left, *T = (*root)->left->right;
    
    // Perform rotation
    x->right = *root;    // Make x the new root
    (*root)->left = T;     // Make T the left child of root
    
    // Update heights
    (*root)->height = max(height((*root)->left), height((*root)->right)) + 1;
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
struct Node *insert(struct Node *root, int data) {
    // create new node if root is null
    if(root==NULL) {
        root=newNode(data); return root;
    }

    // insert data in the appropriate side of the tree
    if(data<root->key) root->left=insert(root->left,data);
    else if(data>root->key) root->right=insert(root->right,data);
    else return root;

    // get balance factor of the tree
    int b=bal(root);

    // right rotation cases
    if(b>1 && data<root->left->key) return RRot(root);
    if(b>1 && data>root->left->key) {
        // left-right rotation
        root->left=LRot(root->left);
        return RRot(root);
    }

    // left rotation cases
    if(b<-1 && data>root->right->key) return LRot(root);
    if(b<-1 && data<root->right->key) {
        // right-left rotation
        root->right=RRot(root->right);
        return LRot(root);
    }

    // return the unchanged root if tree is balanced
    return root;
}