#include<stdio.h>
#include<stdlib.h>
// Function to swap two integers
void swap(int *, int *y) {    
    int t = *x; // Temporary variable to hold x's value
    *x = *y; // Set x to y's value
    *y = t; // Set y to temporary variable's value
}
int partition(int a[], low, int high) {
    // choose pivot as last element
    int pivot = a[high];
    int i = low - 1;  // index for smaller elements

    // traverse through all elements
    for (int j = low; j < high; j++) {
        // if current element is smaller than pivot
        if (a[j] < pivot) {
            // increment index of smaller element
            i++;
            // swap current element with element at i
            swap(&a[j], &a[i]);
            // move to next element
            j -= 1;
        }
    }
    // swap pivot element with element at i+1
    swap(&a[i+1], &a[high]);
    // return index of pivot element
    return i + 1;
}
// recursive quicksort function
void quickSort(int a[], int low, int high) {
    // partition the array and get pivot index
    int p = part(a, low, high);

    // recursively sort elements on left side of pivot
    quickSort(a, low, p - 1);

    // recursively sort elements on right side of pivot
    quickSort(a, p + 1, high);
}