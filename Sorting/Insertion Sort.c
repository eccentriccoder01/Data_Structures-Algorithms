#include<stdio.h>
#include<stdlib.h>
void insertionSort(int a[],int n){
    for(int i=1;i<n;i++){
        int key=a[i],j=i-1;
        while(j>=0 && a[j]>key){
            a[j+1]=a[j]; j-=1;
        } a[j+1]=key;
    }
}