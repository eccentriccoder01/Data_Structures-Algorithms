#include<stdio.h>
#include<stdlib.h>
// Function to swap two integers
void swap(int *, int *y) {    
    int t = *x; // Temporary variable to hold x's value
    *x = *y; // Set x to y's value
    *y = t; // Set y to temporary variable's value
}
void bubble(int a[],int n){
    // Start bubble sort algorithm
    for(int i=0;i<n-1;i++)
        // Traverse array elements and compare
        for(int j=0;j<n;j++)
            if(a[i]>a[j])
                // Swap if current element is greater than next
                swap(&a[i],&a[j]);
}
