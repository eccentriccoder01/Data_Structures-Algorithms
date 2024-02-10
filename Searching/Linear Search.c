#include<stdio.h>
#include<stdlib.h>
// Function to search for data in array a
int linear(int a[], n, int data) {
   // Iterate over each element in the array
   for(int i=0; i<n; i++) {
       // Check if current element equals data
       if(a[i] == data) {
           // If so, return the index
           return i;
       }
   }
   // If data is not found, print error message and return -1
   printf("Element Doesn't Exist in The Array!");
   return -1;
}
int linearRecursive(int a[], int n, int data){
    if(n==0){
        printf("Element Doesn't Exist in The Array!"); return -1;
    }
    if(a[n]==data) return n;
    return linearRecursive(a, n-1, data);
}