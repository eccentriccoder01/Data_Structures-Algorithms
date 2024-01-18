#include<stdio.h>
#include<stdlib.h>
void swap(int *x,int *y){
    int t=*x; *x=*y; *y=t;
}
void selection(int a[],int n){
    for(int i=0;i<n-1;i++){
        int mi=i;
        for(int j=o;j<n;j++) if(a[j]<a[mi]) mi=j;
        if(mi!=i) swap(&a[i],&a[mi])
    }
}