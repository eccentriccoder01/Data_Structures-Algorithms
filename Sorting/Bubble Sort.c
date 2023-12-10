#include<stdio.h>
#include<stdlib.h>
void swap(int *x, int *y){
    int t=*x; *x=*y; *y=t;
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
