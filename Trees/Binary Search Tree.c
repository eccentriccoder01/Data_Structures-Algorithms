#include<stdio.h>
#include<stdlib.h>
struct Node{int key; struct Node *left, *right;};
struct Node *root=NULL;
// function to find height of the tree
int height(struct Node *root){
    // if root is NULL, return 0 as height
    if(root==NULL) return 0;
    // find height of left subtree and right subtree
    int l=height(root->left), r=height(root->right);
    // if left subtree height is greater, return its height + 1
    // else return right subtree height + 1
    if(l>r) return l+1;
    return r+1;
}
// Allocate memory for new node
struct Node *newNode(int data) {
   // Allocate memory and store data
   struct Node *node = (struct Node*)malloc(sizeof(struct Node));
   node->key = data;  // Set key value
   node->left = NULL;  // Initialize left child as null
   node->right = NULL;  // Initialize right child as null
   return node;  // Return the created node
}
struct Node *minNode(struct Node *root){
    struct Node *curr=root;
    while((curr && curr->left)!=NULL) curr=curr->left;
    return curr;
}
// Find the maximum node in a BST
struct Node *maxNode(struct Node *root){
    struct Node *curr=root; // Initialize current node as root
    while((curr && curr->right)!=NULL) curr=curr->right; // Move right until reaching maximum node
    return curr; // Return the maximum node
}
// insert node with value data
struct Node *insert(struct Node **root, int data){
    // if tree is empty
    if((*root)==NULL) *root=newNode(data);
    // if value is less than root value
    else if(data<(*root)->key) (*root)->left=insert(&(*root)->left,data);
    // if value is greater than root value
    else if(data>(*root)->key) (*root)->right=insert(&(*root)->right,data);
    // if value is already present in tree
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
    // base case: empty tree
    if(root==NULL) return;

    // base case: current level is 1
    if(l==1) printf("%d",root->key);

    // recursive case: current level is greater than 1
    else{
        printGivenLevel(root->left,l-1); // recursively print left subtree
        printGivenLevel(root->right,l-1); // recursively print right subtree
    }
}
void levelorder(struct Node *root){
    int i; // Iterate over levels

    for(i=1;i<=height(root);i++){
        printGivenLevel(root,i); printf("\n"); // Print current level and newline
    }
}
void preorder(struct Node *root){
    // Base case: check if root exists
    if(root!=NULL){
        // Print the root node's key
        printf("%d",root->key);
        // Recursively traverse the left subtree
        preorder(root->left);
        // Recursively traverse the right subtree
        preorder(root->right);
    }
}
void inorder(struct Node *root){
    if(root!=NULL){ // If the node exists
        inorder(root->left); // Traverse left subtree
        printf("%d",root->key); // Print the key
        inorder(root->right); // Traverse right subtree
    }
}
void postorder(struct Node *root){
    if(root!=NULL){ // If node exists
        postorder(root->left); // Traverse left subtree
        postorder(root->right); // Traverse right subtree
        printf("%d",root->key); // Print the node's key
    }
}
struct Node *constructTreeUtil(int post[],int **pi,int key,int min,int max,int size){
    if(*pi<0) return NULL;
    struct Node *root=NULL;
    if(key>min && key<max){
        root=newNode(key); (*pi)-=1;
        if(*pi>=0){
            root->right=constructTreeUtil(post,pi,post[*pi],key,max,size);
            root->left=constructTreeUtil(post,pi,post[*pi],min,key,size);
        }
    } return root;
}
struct Node *constructTree(int post[],int size){
    int pi=size-1;
    return constructTreeUtil(post,&pi,post[&pi],INT_MIN,INT_MAX,size);
}