#include<stdio.h>
#include<stdlib.h>
// Function to search for data in array a
int linear(int a[], n, int data) {
   for(int i=0; i<n; i++) { // Iterate over each element in the array
       if(a[i] == data) { // Check if current element equals data
           return i; // If so, return the index
       }
   }
   // If data is not found, print error message and return -1
   printf("Element Doesn't Exist in The Array!");
   return -1;
}
// Function: linearRecursive
// Input: int array a[], size n, target data
// Output: of data in a[], or -1 if not found
int linearRecursive( a[], int n, int data) {
   // Base case: if n is 0, return -1 if data not found
   if(n==0) {
       printf("Element Doesn't Exist in The Array!");
       return -1;
   }
   // If data is found, return its index
   if(a[n]==data) return n;
   // Recursive case: search in the rest of the array
   return linearRecursive(a, n-1, data); // recursive call
}