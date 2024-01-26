#include<stdio.H>
#include<stdlib.h>
struct Node{int key; struct Node *left, *right; bool r;};
struct Node *newNode(int data) {
   // Allocate memory and store data
   struct Node *node = (struct Node*)malloc(sizeof(struct Node));
   node->key = data;  // Set key value
   node->left = NULL;  // Initialize left child as null
   node->right = NULL;  // Initialize right child as null
   node->r = 0;
   return node;  // Return the created node
}
// Function to find the minimum node in a binary search tree
struct Node *minNode(struct Node *root)
{
    // Initialize current node to root
    struct Node *curr = root;

    // Loop until current node is null or has no left child
    while ((curr && curr->left) != NULL)
    {
        // Move to the left child
        curr = curr->left;
    }

    // Return the minimum node
    return curr;
}
struct Node *insert(struct Node **root, int data) {
    // create new node if root is null
    if (*root == NULL) *root = newNode(data);

    // go to left subtree if data is less than root's key
    if (data < (*root)->key) {
        struct Node *lc = insert((*root)->left, data);
        (*root)->left = lc;  // assign left child
        lc->right = (*root); // make new node as right child of left child
        lc->r = 1;           // set right child count of new node
    } else {
        // go to right subtree if data is greater than or equal to root's key
        struct Node *rc = insert((*root)->right, data);
        (*root)->right = rc; // assign right child
        rc->right = (*root)->right; // make root's right child as right child of new node
        rc->r = (*root)->r; (*root)->r = 0; // update right child count
    }

    // return root node
    return (*root);
}