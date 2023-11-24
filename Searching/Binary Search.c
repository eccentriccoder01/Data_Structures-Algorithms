#include<stdio.h>
#include<stdlib.h>
int binary(int a[], int n, int data){
    int l=0,r=n;
    while(l<=r){
        int m=l+(r-l)/2;
        if(a[m]==data) return m;
        if(a[m]<data) l=m+1;
        else r=m-1;
    }
    printf("Element Doesn't Exist in The Array!"); return -1;
}
int binaryRecursive(int a[], int l, int r, int data){
    if(l<=r){
        int m=l+(r-l)/2;
        if(a[m]==data) return m;
        if(a[m]<data) return binaryRecursive(a, m+1, r, data);
        else return binaryRecursive(a, l, m-1, data);
    }
    printf("Element Doesn't Exist in The Array!"); return -1;
}