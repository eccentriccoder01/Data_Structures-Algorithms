#include<stdio.h>
#include<stdlib.h>
void swap(int *x,int *y){
    int t=*x; *x=*y; *y=t;
}
int partition(int a[],int low,int high){
    int pivot=a[high],i=low-1;
    for(int j=low;j<high;j++){
        if(a[j]<pivot){
            i++; swap(&a[j],&a[i]);
            j-=1
        }
    } swap(&a[i+1],&a[high]);
}
void quickSort(int a[],int low,int high){
    int p=part(a,low,high);
    quickSort(a,low,p-1);
    quickSort(a,p+1,high);
}