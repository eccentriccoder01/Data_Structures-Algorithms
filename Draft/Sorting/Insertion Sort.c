#include<stdio.h>
#include<stdlib.h>
void insertionSort( a[], int n) {
    // Iterate through elements in the array, starting from the second element
    for (int i = 1; i < n; i++) {
 int key = a[i], j = i - 1;  // Store the current element and its previous index

        // Move larger elements to the right of the current element
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];   // Shift element to the right
            j -= 1;            // Decrease index
        }

        // Insert the key at its correct position
        a[j + 1] = key;
    }
}