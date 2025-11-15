#include<stdio.h>
#include<stdlib.h>
// Function to swap two integers
void swap(int *, int *y) {    
    int t = *x; // Temporary variable to hold x's value
    *x = *y; // Set x to y's value
    *y = t; // Set y to temporary variable's value
}
// Function to sort an array using selection sort
void selection(int a[], int n) {
    // Iterate over the array, except for the last element
    for (int i = 0; i < n-1; i++) {
        // Assume the minimum element is the first element of the unsorted part
        int mi = i;
        // Iterate over the unsorted part to find the minimum element
        for (int j = i+1; j < n; j++)
            // If an element is smaller than the current minimum, update the minimum
            if (a[j] < a[mi]) mi = j;
        // If the minimum is not the first element of the unsorted part, swap it with the first element
        if (mi != i) swap(&a[i], &a[mi]);
    }
}