#include<stdio.h>
#include<stdlib.h>
struct Node{int info; struct Node *prev,*next;};
struct Node *start=NULL;
struct Node *newNode(int data){
    struct Node *node=(struct Node*)malloc(sizeof(struct Node));
    node->info=data; node->prev=NULL; node->next=NULL;
    return node;
}
int size(struct Node *start){
    struct Node *curr=start; int i=0;
    while(curr!=NULL){
        curr=curr->next; i++;
    }
    return i;
}
void insertFront(struct Node **start, int data){
    struct Node *node=newNode(data);
    node->next=*start; node->prev=NULL; *start=node;
    if(node->next!=NULL) node->next->prev=node;
    printf('Node Successfully Inserted!');
}
void append(struct Node *start, int data){
    struct Node *curr=start, *node=newNode(data);
    if(start==NULL){
        start=node; node->prev=start;  
        return;
    }
    while(curr->next!=NULL) curr=curr->next;
    curr->next=node; node->prev=curr;
    printf('Node Successfully Inserted!');
}
void insertAtP(struct Node *start, int p, int data){
    struct Node *node=newNode(data), *curr=start;
    if(p>size(start)+1){
        printf("Invalid Position!");
        free(node); return;
    }
    for(int i=1;i<p-1;i++) curr=curr->next;
    node->prev=curr; node->next=curr->next;
    if(node->next!=NULL) node->next->prev=node;
    printf('Node Successfully Inserted!');
}
int deleteFront(struct Node **start){
    if(*start==NULL){
        printf("Underflow!"); return;
    }
    int data=(*start)->info;
    *start=(*start)->next;
    if(*start!=NULL){
    free((*start)->prev);
    (*start)->prev=NULL;
    }
    printf('Node Successfully Deleted!');
    return data;
}
int pop(struct Node **start){
    if(*start==NULL){
    printf("Underflow!"); return -1;
    }
    if((*start)->next==NULL){
        int data=(*start)->info;
        free(*start); *start=NULL;
        return data;
    }
    struct Node *curr=*start;
    while(curr->next->next!=NULL) curr=curr->next;
    int data=curr->next->info;
    free(curr->next); curr->next=NULL;
    printf('Node Successfully Deleted!');
    return data;
}
int deleteAtP(struct Node *start, int p){
    struct Node *curr=start;
    for(int i=0;i<p-2;i++) curr=curr->next;
    int data=curr->next->info;
    curr->next=curr->next->next; curr->next->prev=curr;
    printf('Node Successfully Deleted!');
    return data;
}
void reverse(struct Node **start){
    struct Node *curr=*start, *temp=NULL;
    if((*start==NULL)||((*start)->next==NULL)) return;
    while(curr!=NULL){
        temp=curr->prev;
        curr->prev=curr->next; curr->next=temp;
        curr=curr->prev;
    }
    (*start)=curr; curr->next=NULL;
    printf("List Successfully Reversed!");
}
void display(struct Node *start){

    struct Node *curr=start;
    while(curr->next!=NULL){
        printf("%d ",curr->info);
        curr=curr->next;
    }
    printf("%d",curr->info);
}
void reverseDisplay(struct Node *start){
    if(start==NULL){ printf("The List is Empty!"); return;}
    if(start->next==NULL){ printf("%d",start->info); return;}
    struct Node *curr=start;
    while(curr->next!=NULL) curr=curr->next;
    while(curr->prev!=NULL){
        printf("%d ",curr->info);
        curr=curr->prev;
    }
    printf("%d",curr->info);
}
int main(){
    int choice;
    while(1){ 
        printf("\n\t1 The Size of the List\n");
        printf("\t2 Insert at the Front\n");
        printf("\t3 Insert at the End(Push/Append)\n");
        printf("\t4 Insert at a specified Position\n");
        printf("\t5 Delete from the Front\n");
        printf("\t6 Delete the Last Node(Pop)\n");
        printf("\t7 Delete at a specified Position\n");
        printf("\t8 Reverse the Original List\n");
        printf("\t9 Display the List\n");
        printf("\t10 Display the List in Reverse Order\n");
        printf("\t11 Exit\n");
        printf("Enter the Choice: ");
        scanf("%d",&choice);
    switch(choice){
        case 1: printf("%d",size(start)); break;
        case 2: printf("Enter the Integer to be Inserted: ");
                int data; scanf("%d",&data);
                insertFront(start,data); break;
        case 3: printf("Enter the Integer to be Inserted: ");
                int data; scanf("%d",&data);
                append(start,data); break;
        case 4: printf("Enter the Integer to be Inserted: ");
                int data; scanf("%d",&data);
                printf("Enter the Position(1-Indexed): ");
                int p; scanf("%d",&p);
                insertAtP(start,p,data); break;
        case 5: deleteFront(start); break;
        case 6: pop(start); break;
        case 7: printf("Enter the Position(1-Indexed): ");
                int p; scanf("%d",&p);
                deleteAtP(start, p); break;
        case 8: reverse(start); break;
        case 9: display(start); break;
        case 10: reverseDisplay(start); break;
        case 11: exit(1); break;
        default: printf("Invalid Choice! Try Again: \n"); continue;
    }
    } return 0;
}