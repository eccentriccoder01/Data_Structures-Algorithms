#include<stdio.h>
#include<stdlib.h>
struct Node{int info; struct Node *prev,*next;};
struct Node *start=NULL;
// create new node with data
struct Node *newNode(int data){
    // allocate memory for node
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    // set data, prev, and next of node
    node->info=data; node->prev=NULL; node->next=NULL;
    // return new node
    return node;
}
// create new node with data
// function to find the size of a linked list
int size(struct Node *start){
    // initialize a pointer to the start of the list and a counter to 0
    struct Node *curr=start; int i=0;
    // loop through the list
    while(curr!=NULL){
        // move the pointer to the next node and increment the counter
        curr=curr->next; i++;
    }
    // return the size of the list (the value of the counter)
    return i;
}
void insertFront(struct Node **start, int data){
    // Create new node with given data
    struct Node *node=newNode(data);
    
    // Link new node with current start node
    node->next=*start; node->prev=NULL; *start=node;
    
    // Update previous link of start node if any
    if(node->next!=NULL) node->next->prev=node;
    
    printf('Node Successfully Inserted!');
}
void append(struct Node *start, int data){
    // initialize current and new nodes
    struct Node *curr=start, *node=newNode(data);
    
    // if list is empty, insert new node as start
    if(start==NULL){
        start=node; 
        node->prev=start; 
        return;
    }
    
    // iterate to end of list
    while(curr->next!=NULL) curr=curr->next;
    
    // insert new node at end of list
    curr->next=node; 
    node->prev=curr;
    
    // display success message
    printf('Node Successfully Inserted!');
}
void insertAtP(struct Node *start, int p, int data){
    // create new node
    struct Node *node=newNode(data), *curr=start;
    if(p>size(start)+1){
        printf("Invalid Position!"); // handle invalid position
        free(node); return; // free memory and return
    }
    for(int i=1;i<p-1;i++) curr=curr->next; // navigate to desired position
    node->prev=curr; node->next=curr->next; // connect new node
    if(node->next!=NULL) node->next->prev=node; // adjust pointers if necessary
    printf('Node Successfully Inserted!'); // indicate successful insertion
}
// Delete the front node in the list
int deleteFront(struct Node **start){
    // If the list is empty, return error message
    if(*start==NULL){
        printf("Underflow!"); return;
    }
    // Get the data of the front node
    int data=(*start)->info;
    // Set the front of the list to the next node
    *start=(*start)->next;
    // If there are still nodes after the front, free the memory of the previous front node
    if(*start!=NULL){
    free((*start)->prev);
    // Set the previous node of the new front to NULL
    (*start)->prev=NULL;
    }
    // Print success message
    printf('Node Successfully Deleted!');
    // Return the deleted data
    return data;
}
// Function to remove and return top element from stack
int pop(struct Node **start){
    // Check if stack is empty
    if(*start==NULL){
        printf("Underflow!"); 
        return -1;
    }
    // Check if stack contains only 1 element
    if((*start)->next==NULL){
        int data=(*start)->info;
        free(*start); 
        *start=NULL;
        return data;
    }
    // Initialize pointer to traverse stack
    struct Node *curr=*start;
    // Find second last element in stack
    while(curr->next->next!=NULL) curr=curr->next;
    // Get data from second last element and remove it
    int data=curr->next->info;
    free(curr->next); 
    curr->next=NULL;
    printf('Node Successfully Deleted!');
    return data;
}
// Delete node at given position
int deleteAtP(struct Node *start, int p){
    struct Node *curr=start;

    // Loop to the previous node of the node to be deleted
    for(int i=0;i<p-2;i++) curr=curr->next;

    // Get the value of the node to be deleted
    int data=curr->next->info;

    // Remove the node by updating the pointers of previous and next nodes
    curr->next=curr->next->next; curr->next->prev=curr;

    printf('Node Successfully Deleted!');
    return data;
}
void reverse(struct Node **start){
    struct Node *curr=*start, *temp=NULL; // set current and temp nodes

    if((*start==NULL)||((*start)->next==NULL)) return; // check if list is empty or has only one node

    while(curr!=NULL){
        temp=curr->prev; // save previous node
        curr->prev=curr->next; curr->next=temp; // swap prev and next pointers
        curr=curr->prev; // move to next node
    }

    (*start)=curr; // update start pointer
    curr->next=NULL; // set last node's next pointer to NULL

    printf("List Successfully Reversed!");
}
void display(struct Node *start){
    // initialize current pointer to start
    struct Node *curr=start;
    // loop through linked list
    while(curr->next!=NULL){
        printf("%d ",curr->info);
        curr=curr->next; // move to next node
    }
    printf("%d",curr->info); // print last node
}
void reverseDisplay(struct Node *start){
    // Check if the list is empty
    if(start==NULL){ 
        printf("The List is Empty!"); 
        return;
    }

    // If there is only one node in the list
    if(start->next==NULL){ 
        printf("%d",start->info); 
        return;
    }

    // Set current node to the start of the list
    struct Node *curr=start;

    // Traverse the list to the end
    while(curr->next!=NULL) curr=curr->next;

    // Traverse the list in reverse order and print the data
    while(curr->prev!=NULL){
        printf("%d ",curr->info);
        curr=curr->prev;
    }

    // Print the last node data
    printf("%d",curr->info);
}

//Driver's Code
int main(){
    int choice;
    while(1){ 
        printf("\n\t1 The Size of the List\n"); // Get size
        printf("\t2 Insert at the Front\n"); // Insert at front
        printf("\t3 Insert at the End(Push/Append)\n"); // Insert at end
        printf("\t4 Insert at a specified Position\n"); // Insert at specified position
        printf("\t5 Delete from the Front\n"); // Delete from front
        printf("\t6 Delete the Last Node(Pop)\n"); // Delete last node
        printf("\t7 Delete at a specified Position\n"); // Delete at specified position
        printf("\t8 Reverse the Original List\n"); // Reverse the list
        printf("\t9 Display the List\n"); // Display the list
        printf("\t10 Display the List in Reverse Order\n"); // Display the list in reverse order
        printf("\t11 Exit\n"); // Exit the program
        printf("Enter the Choice: ");
        scanf("%d",&choice);
    switch(choice){
        case 1: printf("%d",size(start)); break; // Print size
        case 2: insertFront(start,data); break; // Insert at front
        case 3: append(start,data); break; // Insert at end
        case 4: insertAtP(start,p,data); break; // Insert at specified position
        case 5: deleteFront(start); break; // Delete from front
        case 6: pop(start); break; // Delete last node
        case 7: deleteAtP(start, p); break; // Delete at specified position
        case 8: reverse(start); break; // Reverse the list
        case 9: display(start); break; // Display the list
        case 10: reverseDisplay(start); break; // Display the list in reverse order
        case 11: exit(1); break; // Exit the program
        default: printf("Invalid Choice! Try Again: \n"); continue; // Invalid choice, try again
    }
    } return 0;
}