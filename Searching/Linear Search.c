#include<stdio.h>
#include<stdlib.h>
int linear(int a[], int n, int data){
    for(int i=0;i<n;i++) if(a[i]==data) return i;
    printf("Element Doesn't Exist in The Array!"); return -1;
}
int linearRecursive(int a[], int n, int data){
    if(n==0){
        printf("Element Doesn't Exist in The Array!"); return -1;
    }
    if(a[n]==data) return n;
    return linearRecursive(a, n-1, data);
}