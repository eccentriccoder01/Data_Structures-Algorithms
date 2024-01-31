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
void selection(int a[],int n){
    for(int i=0;i<n-1;i++){
        int mi=i;
        for(int j=o;j<n;j++) if(a[j]<a[mi]) mi=j;
        if(mi!=i) swap(&a[i],&a[mi])
    }
}