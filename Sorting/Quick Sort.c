#include<stdio.h>
#include<stdlib.h>
// Function to swap two integers
void swap(int *, int *y) {    // Temporary variable to hold x's value
   int t = *x;
   
   // Set x to y's value
*x = *y;

   // Set y to temporary variable's value
   *y = t;
}
int partition(int a[],int low,int high){
    int pivot=a[high],i=low-1;
    for(int j=low;j<high;j++){
        if(a[j]<pivot){
            i++; swap(&a[j],&a[i]);
            j-=1
        }
    } swap(&a[i+1],&a[high]);
}
void quickSort(int a[],int low,int high){
    int p=part(a,low,high);
    quickSort(a,low,p-1);
    quickSort(a,p+1,high);
}